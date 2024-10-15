#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <mariadb/mysql.h>
#include <stdbool.h>
#include <pthread.h>

#define BUF_SIZE 1024
#define HTTP_PORT 3001  // React 요청을 처리할 포트
#define TCP_PORT 9100   // 아두이노와 통신할 포트

static bool state = false;  // 전역 상태 변수

// MySQL 연결 정보
char *server = "localhost";
char *user = "root";
char *password = "damdam";
char *database = "dht_testDB";

void error_handling(char *message);
void *handle_tcp_arduino(void *arg);
void handle_http_request(int clnt_sock, MYSQL *conn);
void handle_get_data(int clnt_sock, MYSQL *conn);
void handle_post_state(int clnt_sock, MYSQL *conn);

int main() {
    // TCP 및 HTTP 서버를 병렬로 실행하기 위해 스레드를 사용
    pthread_t tcp_thread;
app.get('/api/data', (req, res) => {
        const query = 'SELECT * FROM temp_humi ORDER BY id DESC LIMIT 1';
        db.query(query, (err, result) => {
                if(err){
                res.status(500).send(err);
               } else{
               res.json(result[0]);
               }
               });
        });
    int tcp_result = pthread_create(&tcp_thread, NULL, handle_tcp_arduino, NULL);
    if (tcp_result != 0) {
        error_handling("TCP 스레드 생성 실패");
    }

    // HTTP 서버 설정
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

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

    // HTTP 소켓 설정
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

    clnt_adr_sz = sizeof(clnt_adr);

    // HTTP 요청 처리 루프
    while (1) {
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

// TCP 소켓을 통한 아두이노 통신 처리 (별도 스레드)
void *handle_tcp_arduino(void *arg) {
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        pthread_exit(NULL);
    }

    if (mysql_real_connect(conn, server, user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        pthread_exit(NULL);
    }

    // TCP 소켓 설정
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("TCP socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(TCP_PORT);

    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1) {
        error_handling("TCP bind() error");
    }

    if (listen(serv_sock, 5) == -1) {
        error_handling("TCP listen() error");
    }

    clnt_adr_sz = sizeof(clnt_adr);

    while (1) {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        if (clnt_sock == -1) {
            error_handling("TCP accept() error");
        }

        char message[BUF_SIZE];
        int str_len = read(clnt_sock, message, BUF_SIZE - 1);
        if (str_len > 0) {
            message[str_len] = 0;  // 문자열 끝 처리
            printf("Received data from Arduino: %s\n", message);

            // 온습도 데이터를 :와 L로 분리
            char *temp_str = strtok(message, ":");
            char *humi_str = strtok(NULL, "L");
            int temp = atoi(temp_str);
            int humi = atoi(humi_str);

            // MySQL에 온습도 데이터 저장
            char query[128];
            sprintf(query, "INSERT INTO temp_humi (temp, humi, state) VALUES (%d, %d, %d)", temp, humi, state);
            if (mysql_query(conn, query)) {
                fprintf(stderr, "INSERT error: %s\n", mysql_error(conn));
            } else {
                printf("Data inserted: temp=%d, humi=%d\n", temp, humi);
            }

            // 클라이언트로 에코 응답
            char response[64];
            sprintf(response, "temp=%d, humi=%d", temp, humi);
            write(clnt_sock, response, strlen(response));
        }
        close(clnt_sock);
    }

    mysql_close(conn);
    close(serv_sock);
    pthread_exit(NULL);
}

// HTTP 요청 처리 함수
void handle_http_request(int clnt_sock, MYSQL *conn) {
    char buffer[BUF_SIZE];
    int str_len = read(clnt_sock, buffer, BUF_SIZE - 1);
    if (str_len <= 0) return;

    buffer[str_len] = 0;  // 문자열 끝 처리
    printf("HTTP Request: %s\n", buffer);

    // OPTIONS 요청에 대한 CORS 설정 (사전 요청 처리)
    if (strstr(buffer, "OPTIONS") != NULL) {
        char cors_header[] = "HTTP/1.1 204 No Content\r\n"
                             "Access-Control-Allow-Origin: *\r\n"
                             "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
                             "Access-Control-Allow-Headers: Content-Type\r\n"
                             "Content-Length: 0\r\n\r\n";
        write(clnt_sock, cors_header, sizeof(cors_header) - 1);
        return;
    }

    // GET /api/data 요청 처리
    if (strstr(buffer, "GET /api/data") != NULL) {
        handle_get_data(clnt_sock, conn);
    }
    // POST /api/state 요청 처리
    else if (strstr(buffer, "POST /api/state") != NULL) {
        handle_post_state(clnt_sock, conn);
    } else {
        // 응답 헤더
        char response[] = "HTTP/1.1 404 Not Found\r\n"
                          "Access-Control-Allow-Origin: *\r\n"
                          "Content-Length: 13\r\n\r\n404 Not Found";
        write(clnt_sock, response, sizeof(response) - 1);
    }
}

// GET /api/data 요청 처리 함수
void handle_get_data(int clnt_sock, MYSQL *conn) {
    char query[] = "SELECT temp, humi FROM temp_humi ORDER BY id DESC LIMIT 1";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "SELECT error: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);

    // 응답 데이터 생성
    char data[128];
    sprintf(data, "{\"temp\": %s, \"humi\": %s}", row[0], row[1]);

    // 응답 헤더
CP_PORT 9100   // 아두이노와 통신할 포트

    char header[] = "HTTP/1.1 200 OK\r\n"
                    "Access-Control-Allow-Origin: *\r\n"
                    "Content-Type: application/json\r\n";
    char content_length[50];
    sprintf(content_length, "Content-Length: %lu\r\n\r\n", strlen(data));

    // 응답 전송
    write(clnt_sock, header, strlen(header));
    write(clnt_sock, content_length, strlen(content_length));
    write(clnt_sock, data, strlen(data));

    mysql_free_result(res);
}

// POST /api/state 요청 처리 함수
void handle_post_state(int clnt_sock, MYSQL *conn) {
    // 상태를 토글
    state = !state;
    printf("State changed: %d\n", state);

app.get('/api/data', (req, res) => {
        const query = 'SELECT * FROM temp_humi ORDER BY id DESC LIMIT 1';
        db.query(query, (err, result) => {
                if(err){
                res.status(500).send(err);
               } else{
               res.json(result[0]);
               }
               });
        });

    // 데이터베이스에 상태 업데이트
    char query[128];
    sprintf(query, "UPDATE temp_humi SET state = %d ORDER BY id DESC LIMIT 1", state);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "UPDATE error: %s\n", mysql_error(conn));
    } else {
    // 응답 헤더
    char response[] = "HTTP/1.1 200 OK\r\n"
                      "Access-Control-Allow-Origin: *\r\n"
                      "Content-Length: 0\r\n\r\n";
    write(clnt_sock, response, sizeof(response) - 1);
        printf("State updated in database\n");
    }

    // 응답 헤더
    char response[] = "HTTP/1.1 200 OK\r\n"
                      "Access-Control-Allow-Origin: *\r\n"
                      "Content-Length: 0\r\n\r\n";
    // 응답 헤더
    char response[] = "HTTP/1.1 200 OK\r\n"
                      "Access-Control-Allow-Origin: *\r\n"
                      "Content-Length: 0\r\n\r\n";
    write(clnt_sock, response, sizeof(response) - 1);
    write(clnt_sock, response, sizeof(response) - 1);
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}



