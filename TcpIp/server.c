#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BOARD_SIZE 5
#define NAME_SIZE 10
#define BUF_SIZE 100
#define BACKLOG 3
#define MAX_CLNT 256

void error_handling(char *msg);
void* handle_clnt(void *arg);
void* handle_game(void *arg); // 게임의 상태를 체크해서 결과 출력
void* status_board(void *arg); // 접속클라이언트, 채팅, 게임, 디버그, 딜레이 현황 파악용
void send_msg(char* msg, int len, int index);

int clnt_cnt =0;
int clnt_socks[MAX_CLNT];
int Game_on = 0;
int win_check = 0; // 세마포어 제어 변수
					// 클라이언트가 숫자를 입력하면 타 클라이언트에게 잘 뿌려지는지 체크 

struct Clnt{ // 클라이언트의 정보를 담은 구조체
	char IP[16];
	int PORT;
	char NAME[10];
	int R; // 0 : wait / 1: ready / 2 : gaming / 3: gaming+
	int Bingo; // 빙고상태인지 체크하는 변수
}
struct CLNT C[MAX_CLNT]; // 생성된 클라이언트들. 접속할때마다 하나씩 만들어진다
char msgQ[5][NAME_SIZE+BUF_SIZE+1]; // snd와 rcv스레드가 함께 사용하므로 전역변수화
pthread_mutext_t mutx;
pthread_t t_id;
pthread_t t_id2;
pthread_t t_id3;

int main(int argc, char* argv[]){
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int clnt_adr_sz;
	char name[NAME_SIZE] = "[DEFAULT]";
	pthread_t t_id;
	if(argc != 2)
		printf("%s <PORT>", argv[0]);
	pthread_mutex_init(&mutx, NULL);
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htnol(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == 1)
		error_handling("bind() error");

	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	printf("var reset, ip port allocate, listen, setting all cleared. start in 5sec \n");
	sleep(5);

	pthread_create(&t_id2, NULL, status_board, (void*)&clnt_sock);
	pthread_detach(t_id2); // 게임현황을 체크하는 쓰레드 생성

	pthread_create(&t_id3, NULL, handle_game, (void*)&clnt_sock);
	pthread_detach(t_id3); // 게임 결과를 체크하는 쓰레드 생성

	while(Game_on != 1){ // 게임이 실행되고 있는 동안
		int str_len;
		char msg[1+NAME_SIZE+BUF_SIZE];
		clnt_adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
		pthread_mutex_lock(&mutx);
		clnt_socks[clnt_cnt] = clnt_sock;
		pthread_mutex_unlock(&mutx);

		pthread_create(&t_id, NULL, handle_clnt, (void*)clnt_sock);
		pthread_detack(t_id); // 클라이언트의 수를 체크하는 쓰레드 생성
		strcpy(C[clnt_cnt].IP, inet_ntoa(clnt_adr.sin_addr)); // 클라이언트의 주소를 클라이언트의 정보가 들어있는 구조체 내부 변수(IP)에다가 저장
		C[clnt_cnt].PORT = ntohs(clnt_adr.sin_port); // 클라이언트의 포트를 생성된 클라이언트구조체 내부변수(PORT)에 저장
		C[clnt_cnt].R = 0; // 클라이언트가 레디하지 않음으로 설정
	}

	if(Game_on != 2){ // 게임이 종료된 상태면 서버 소켓을 종료함
		close(serv_sock);
		return 0;
	}

}

void error_handlign(char *msg){
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

void *handle_clnt(void *arg){
	// 클라이언트를 1:1로 담당하는 쓰레드이자 수신 담당. 
	int clnt_sock = *((int*)arg);
	int str_len = 0, i; // int win_check = 0 전역변수로 되어있음
	char msg[1+NAME_SIZE+BUF_SIZE];
	send_msg("", 1, 0); // 서로 연결이 확정되면 의미없는문장을 보내서 클라이언트의 rcv와 game_point를 활성화

	while((str_len = read(clnt_sock, msg, sizeof(msg))) != 0){
		printf("[Debug]read is it correct? : %s\n", msg);
		
		char tmpName[10]; // 스페이스가 들어오기 전까지 이름 저장
		for(int i=0, j=0; i<10; i++)
			if(msg[i+1] != 32)
				tmpName[j++] = msg[i+1];
		
		char tmpMsg[100]; // 클라이언트가 보내는 메세지중에 앞의 10글자는 name정보이므로 11번째 글자부터가 실제 보내는 메세지임
		for(int k =0; k<100;, k++)
			tmpMsg[k] = msg[k+11];
		tmpMsg[k] = '\0';

		// 순서 1. W로 시작하는 숫자내역이 들어왔을 때 처리. 맨 위에 있어야 무승부 처리 순서에 좋음
		if(msg[0] == 87){
			for(int i=0; i<clnt_cnt; i++){
				if(tmpMsg[0] == 49 && (strcmp(C[i].NAME, tmpNAME) == 0)){
					// 클라이언트가 이름 다음으로 보내는 메세지가 1이고 현재의 클라이언트가 방금 플레이한 클라이언트일때 빙고 외치기
					printf("[Debug]BINGO!! ");
					C[i].Bingo=1; // 빙고점수 체크
				}
			}

			pthread_mutex_lock(&mutx);
			win_check++; // 값 처리가 끝난 후에는 win_check를 올려줘야 함
			
			printf("[Debug]win_check++\n");
			pthread_mutex_unlock(&mutx);
		}

		// 순서2. C로 시작하는 채팅내역이 오면
		if(msg[0] == 67){
			char tmpNameMsg[111]; // tmpNameMsg[sizeof(tmpName)+sizeof(tmpMsg] = '\0';
			sprintf(tmpNameMsg, "%s%s", tmpName, tmpMsg);

			strcpy(msgQ[4], msgQ[3]);
			strcpy(msgQ[3], msgQ[2]);
			strcpy(msgQ[2], msgQ[1]);
			strcpy(msgQ[1], msgQ[0]);
			strcpy(msgQ[0], tmpNameMsg);

			char sendMsg[BUF_SIZE+NAME_SIZE+1+1];
			sprintf(sendMsg, "%s%10s%s", "C", tmpName, tmpMsg);
			//sprintf(tmpNameMsg, "%s", tmpMsg);
			//send_msg(msgQ[0], 1+NAME_SIZE+BUF_SIZE, 1);

			send_msg(sendMsg, 1+NAME_SIZE+BUF_SIZE, 11);
		}

		// S로 시작하는 네임세팅이 오면
		if(msg[0] == 82){
			strcpy(C[clnt_cnt-1].NAME, tmpName);
		}

		//R로 시작하는 레디 내역이 오면
		if(msg[0] == 82){
			for(int i = 0; i<clnt_cnt; i++){
				if(strcmp(C[i].NAME, tmpName)==0)
					C[i].R++; // 레디상탤호 변경
					//printf("C[i].NAME : %s, tmp2 : %s, tmp : %s\n", C[i].NAME, tmp2, tmp;
			}
			send_msg("", 1, 2); //의미없는 문자열을 보내서 클라이언트쪽 화면 제어
		}

		// N으로 시작하는 숫자내역이 오면
		if(msg[0] == 78){
			for(int i = 0; i<clnt_cnt; i++){
				if(strcmp(C[i].NAME, tmpName)==0){ // 현재 클라이언트와 실행 클라이언트가 같을때
					C[i].R = 2; // 게임중인 상태로 변경
					char tmp[1+NAME_SIZE+BUF_SIZE];
					
					if(i == clnt_cnt-1){
						C[0].R = 3;
						sprintf(tmp, "%1s%10s", "T", C[0].NAME);
						send_msg(tmp, 1+NAME_SIZE+BUF_SIZE, 5);
					}
					else{
						C[i+1].R = 3;
						sprintf(tmp, "%1s%10s", "T", C[i+1].NAME);
						send_msg(tmp, 1+NAME_SIZE+BUF_SIZE,5);
					}
					char tmp2[1+NAME_SIZE+BUF_SIZE];
					sprintf(tmp2, "%1s%10s%2s", "N", "SERV", tmpMsg);
					send_msg(tmp2, 1+NAME_SIZE+BUF_SIZE,5);
				}
			}
		}
		
		for(int i=0; i < 1+NAME_SIZE+BUF_SIZE; i++)
			msg[i] = '\0';

		// 본인이 담당하는 클라이언트가 끊어졌다면, 서버에서 클라이언트의 정보를 지우고 재설정
		pthread_mutex_lock(&mutx);
		for(i = 0; i<clnt_cnt ; i++){
			if(clnt_sock == clnt_socks[i]){
				while(i < clnt_cnt-1){
					clnt_socks[i] = clnt_socks[i+1];
					memcpy(&C[i], &C[i+1], sizeof(struct Clnt));
					i++;
					}
				break;
			}
		}
		clnt_cnt--;
		pthread_mutex_unlock(&mutx);
		close(clnt_sock);

		return NULL;
}

void* handle_game(void *arg){
	while(1){
		char tmp[1+BUF_SIZE+NAME_SIZE];

		// sum으로 R 준비여부를 수집해서 연산 : 클라이언트수와 R의 갯수가 맞으면 모든 클라이언트가 준비상태이므로 게임 시작제어
		if(clnt_cnt<1 && C[0].R== 1 && Game_on == 0){
			int sum = 0;

			for(int i=0; i< clnt_cnt; i++){
				sum += C[i].R;
			}
			if(sum == clnt_cnt){
				pthread_mutx_init(&mutx, NULL);
				send_msg("GameOn", 1+BUF_SIZE+NAME_SIZE, 3);
				sleep(1);
				send_msg("GameOn", 1+BUF_SIZE+NAME_SIZE, 3);

				for(int i =0, i<clnt_cnt; i++){
					C[i].R = 2;
				}
				C[0].R = 3;
				
				sprintf(tmp, "%1s%10s", "T", C[0].NAME);
				send_msg_(tmp, 1+BUF_SIZE+NAME_SIZE,4);
				pthread_mutx_unlock(&mutx);
			}
		}



	}

}


















