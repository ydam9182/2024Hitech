#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>
#include <stdbool.h>
#include <pthread.h>

#define BUF_SIZE 1024
#define HTTP_PORT 3001  // React 요청을 처리할 포트
#define ESP_PORT 9100   // 아두이노와 통신할 포트

static bool door_state = false;  //  문을 원격제어할 상태변수

// MySQL 연결 정보
char *server = "localhost";
char *user = "root";
char *password = "damdam";
char *database = "SmartBuilding";

void error_handling(char *message);
void connet_mysql(void);
void *handle_esp(void *arg);
void handle_http_request(int clnt_sock, MYSQL *conn);
void handle_get_data(int clnt_sock, MYSQL *conn);
void handle_post_state(int clnt_sock, MYSQL *conn);

int main() { // TCP 및 HTTP 서버를 병렬로 실행하기 위해 스레드를 사용
    //데이터베이스 접속
    connect_mysql();

    //esp용 스레드 생성
    pthread_t esp_thread; 

    int esp_result = pthread_create(&esp_thread, NULL, handle_esp, NULL); // handle_esp라는 함수로 스레드 생성
    if (esp_result != 0) 
        error_handling("ESP 스레드 생성 실패");


    // HTTP 서버 설정 -> 보내야할 값이 있으므로 여기서 HTTP 서버 소켓 설정
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("HTTP socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(HTTP_PORT);

    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("HTTP bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("HTTP listen() error");

    // HTTP 요청 처리 루프
    while (1) {
        clnt_adr_sz = sizeof(clnt_adr);

         // serv_sock을 통해 들어오는 HTTP_clnt가 있을때 clnt_socket 생성
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        if (clnt_sock == -1)
            error_handling("HTTP accept() error");

        handle_http_request(clnt_sock, conn);  // HTTP 요청 처리
        //close(clnt_sock);
    }

    mysql_close(conn);
    close(serv_sock);
    return 0;
}

void connet_mysql(void){ // mysql 커넥트 설정
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, server, user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        exit(1);
    }
}

// TCP 소켓을 통한 ESP 처리 (별도 스레드)
void *handle_esp(void *arg) {
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    //데이터베이스 접속
    connect_mysql();

    // TCP 소켓 설정
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("TCP socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(ESP_PORT);

    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1) 
        error_handling("ESP bind() error");

    if (listen(serv_sock, 5) == -1) 
        error_handling("ESP listen() error");

    clnt_adr_sz = sizeof(clnt_adr);

    while (1) {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz); 
        // 서버소켓을 통해 접속을 시도할때 클라이언트 소켓 생성

        if (clnt_sock == -1) 
            error_handling("ECP accept() error");

        char message[BUF_SIZE]; // Esp에서 넘어올 값
        char response[64]; //Esp에 에코로 넘겨줄 값

        int str_len = read(clnt_sock, message, BUF_SIZE - 1); //클라이언트소켓 내부로 타고들어온 메세지 처리
        if (str_len > 0) {
            message[str_len] = 0;  // 문자열 끝 처리
            printf("Received data from ESP: %s\n", message);

            // 전달값을 : 기준으로 분리 -> 아두이노 전달값 "RoomNo:state:img_path"
            char *state = strtok(message, ":");
            char *img_path = strtok(NULL, "");

            // door를 패스워드 실패,성공시 처리해줄 로직 구성
            // 성공시 출력하고 그냥 끝
            if(state == "Sucess"){
                sprintf(response, "Door Opned!\n");
            }
            // 문을 5번 못열었을때 => 아두이노에서 "5Fail"이라는 메세지를 보냄
            if(state == "5Fail"){
                sprintf(response, "Caution! Visit Stranger!\n");//경고문 한번 띄우고
                
                // 데이터베이스에 들어온 이미지 패스값을 저장
                char query[128];
                sprintf(query, "INSERT INTO Timer (Imagepath) VALUES (%s)", img_path);
                if (mysql_query(conn, query)) {
                    fprintf(stderr, "INSERT error: %s\n", mysql_error(conn));
                } else {
                    printf("Data inserted: img_path = %s\n", img_path);
                }
            }
            // 클라이언트로 에코 응답            
            write(clnt_sock, response, strlen(response));
        }
        close(clnt_sock);
    }

    mysql_close(conn);
    close(serv_sock);
    pthread_exit(NULL);
}
