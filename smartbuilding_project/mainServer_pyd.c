#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024
#define MAX_CLNT 10 // 접속할수 있는 방 갯수
#define PORT 9000

int clnt_cnt = 0; // 클라이언트 수를 0으로 초기화
int clnt_socks[MAX_CLNT][4]; // 최대 입장할 수 있는 클라이언트들과 클라이언트들의 관리소켓
//clnt_socks의 첫번째 인자는 roomNo을 저장할곳, 2번째 인자값부턴 esp, cam, web의 소켓이 들어갈 곳
pthread_mutex_t mutx; //뮤텍스에 선언

//MySql 연결정보
char* server = "localhost";
char* user= "root";
char* password = "damdam";
char* database="SmartBuilding";

void *handle_clnt(void *arg); //클라이언트들을 관리할 함수
void handle_role(int roomNo_id, int clnt_sock, char* message, MySQL* conn); 
// 변수 clnt는 룸 넘버를 저장한 포인터
// 클라이언트들의 메세지를 분리해서 각자 역할을 지정할 함수. 
// 메세지를 분리해서 각각의 하드웨어 파트별로 나눠줌
void handle_esp(int roomNo, int clnt_sock, char* message, MYSQL* conn); // esp를 핸들링할 함수
void handle_cam(int roomNo, int clnt_sock, char* message, MYSQL *conn); // cam를 핸들링할 함수
void handle_web(int roomNo, int clnt_sock, char* message, MYSQL* conn); // 웹페이지를 핸들링할 함수
void save_imgPath(MYSQL* conn, const char* imgPath, const char* roomNo); // 이미지 경로를 요청할 저장할 함수
void error_handling(char *msg); // 에러메세지를 출력할 함수

int mian(){
    int serv_sock, clnt_sock; // 클라언트들의 소켓은 통합으로 관리
    struct sockaddr_in serv_sock, clnt_adr;
    int clnt_adr_sz;
    pthread_t thread;
    pthread_mutex_init(&mutx, NULL);

    //MySql init
    MYSQL* conn = mysql_init(NULL);
    if(mysql_real_connect(conn, server, user, password, database, 0, NULL, 0) == NULL)
        error_handling("mysql_real_connect() failed!");

    //TCP 소켓 설정
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock < 0)
        error_handling("Socket creation error");

    memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(PORT);

	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	if(listen(serv_sock, MAX_CLNT)==-1)
		error_handling("listen() error");

    printf("Server listen on port %d...\n", PORT);

    while(1){
        clnt_adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz); //클라이언트 요청이 들어오면 받아들이고

		pthread_create(&thread, NULL, handle_clnt, (void *)&clnt_sock); // handle_clnt라는 스레드로 따로 추출
		pthread_detach(thread);
		printf("Connected client IP : %s\n", inet_ntoa(clnt_adr.sin_addr)); //현재 접속된 아이피 출력해보기
    }

    close(serv_sock); // 서버가 종료되면 소켓닫기
    pthread_mutex_destroy(&mutex); //뮤텍스도 끝나고
    mysql_close(conn); //mysql도 끝

    return 0;
}

void* handle_clnt(void *arg){ // 각자 들어온 클라이언트들의 기능을 나눠줄 함수
    int clnt_sock = *((int*)arg);
    char msg[BUF_SIZE];
    char roomNo[5] = {0};
    clnt_cnt++; // 클라이언트가 들어왔으므로 카운트 높여주고

    //MySql init
    MYSQL* conn = mysql_init(NULL);
    if(mysql_real_connect(conn, server, user, password, database, 0, NULL, 0) == NULL)
        error_handling("mysql_real_connect() failed!");

    read(clnt_sock, msg, sizeof(msg)); //메세지를 처음 읽어와서 msg라는 버퍼에 저장
    roomNo = strtok(msg, ":"); // 메세지의 앞머리를 따서 roomNo변수에 저장

    //현재 들어온 클라이언트가 roomNo중에 일치하는 값이 있다면 이미 생성된 room인 것 
    for(int i=0; i < clnt_cnt; i++){
        if(clnt_socks[i][0] == roomNo){ 
            printf("Existed Client!\n");
            handle_role(i, clnt_sock, msg, conn); // i를 roomNo의 인덱스값으로 넘겨줌.
            clnt_cnt--; //이미 있는 클라이언트이므로 숫자를 늘려줄 필요 없음. 
        }
    }
    
    // 만약 들어온 클라이언트가 기존 클라이언트들중에 없었던 것이라면 새로운 클라이언트 생성, 배열에 첫번째는 roomNO으로 지정
    clnt_socks[clnt_cnt][0] = roomNo;
    printf("new Room\n");
    handle_role(roomNo, clnt_sock, msg, conn); // 새로운 room의 역할 배치 init

    mysql_close(conn); //mysql도 끝
    return NULL;
}

void handle_role(int roomNo_id, int clnt_sock, char* msg, MYSQL* conn){
    char role[10] = strtok(null, ":"); // 들어온 데이터의 하드웨어를 검색해서 각자의 처리함수로 넘겨주기

     // 생성된 room에서 해당 role(esp, cam, web)의 소켓이 배정되어 있지 않았다면 각자 자리로 넣어줌. 
     // 이미 생성된 role소켓이라면 소켓을 닫기전까진 계속 소통중이므로 최초 1회만 실행되고 끝나게 될것.
     if(role == "ESP"){
         clnt_sock[roomNo_id][1] = clnt_sock; // esp의 소켓fd을 저장
         handle_esp(roomNo, clnt_sock, msg, conn);
     }
     else if(role == "cam"){
         clnt_sock[roomNo_id][2] = clnt_sock; // cam의 소켓fd을 저장
         handle_cam(roomNo, clnt_sock, msg, conn);
     }
     else if(role == "web"){
         clnt_sock[roomNo_id][3] = clnt_sock; // web의 소켓fd을 저장
         handle_web(roomNo, clnt_sock, msg, conn);
     }

     return NULL;
}

void error_handling(char * msg){
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
