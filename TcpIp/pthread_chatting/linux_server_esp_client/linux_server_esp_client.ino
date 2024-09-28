#include "WiFiEsp.h"
#include <SoftwareSerial.h>
#include <stdio.h>
#include <string.h>

// 소프트웨어 직렬 포트를 통해 ESP8266과 통신
SoftwareSerial Serial1(10, 11); // RX, TX

// Wi-Fi 네트워크 정보
char ssid[] = "test01";        // Wi-Fi 네트워크 이름
char pass[] = "12341234";    // Wi-Fi 비밀번호

// 리눅스 채팅 서버 정보
char server_ip[] = "192.168.0.4";  // 리눅스 서버 IP 주소
int server_port = 9100;              // 리눅스 서버 포트 번호

WiFiEspClient client;  // Wi-Fi 클라이언트 객체

void setup() {
  // 시리얼 통신 시작 (디버깅용)
  Serial.begin(9600);
  Serial1.begin(9600);  // ESP8266과의 소프트웨어 직렬 통신 시작

  // ESP8266 초기화
  WiFi.init(&Serial1);

  // Wi-Fi 연결 확인
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi 모듈을 찾을 수 없습니다.");
    while (true);
  }

  // Wi-Fi 네트워크에 연결
  connectToWiFi();

  // 리눅스 채팅 서버에 연결
  if (client.connect(server_ip, server_port)) {
    Serial.println("서버에 성공적으로 연결되었습니다.");
    client.println("Yedam의 ESP8266 채팅 클라이언트");  // 서버에 첫 메시지 전송
  } else {
    Serial.println("서버에 연결할 수 없습니다.");
  }
}

void loop() {
  // 서버로부터 메시지를 수신
  if (Serial1.available()) {
    // char serverMsg[100] = {0};
    // static int i = 0;
    // serverMsg[i++] = Serial1.read();
    // char buffer[100] = {0};
    // sprintf(buffer, "%s", serverMsg);

    // String serverMsg = Serial1.readStringUntil('\n');
    // Serial.print("받은 메시지: ");
    // Serial.println(serverMsg); 서버로부터 받은 메시지 출력 

    // if((serverMsg.equals("q\n\n")) || (serverMsg.equals("Q\n\n"))){ // 들어온 값이 q이면 소켓닫기
    //   Serial.println("서버와의 연결을 닫습니다");
    //   client.stop();
    //   while (true);  // 클라이언트 연결이 끊어지면 멈춤
    // }

    char serverMsg[100] = {0};
    static int i = 0;
    
    //Serial.println(msgT);
    serverMsg[i++] = Serial1.read();
    if(serverMsg[i-1] != '\n'){ // 개행이 들어오기 전까지 입력 받기
      char *buffer = strtok(serverMsg, '#'); //앞 값은 버리고
      while(buffer != NULL){
        buffer = strtok(NULL, '\n') ; //뒤 값만 읽어오기
        Serial.print("서버 메시지: ");    
        Serial.println(buffer);  // 서버로부터 받은 메시지 출력    
      }
      i = 0;   
    }
    // else{ //개행이 들어오면
      
    // }   
  }

  // 사용자가 입력한 메시지를 서버로 전송 //send
  if (Serial.available()) {
    String userMsg = Serial.readStringUntil('\n');

    client.println(userMsg);  // 입력한 메시지를 서버로 전송
    Serial.print("보낸 메시지: ");
    Serial.println(userMsg);
    //delay(100);
  }

  // 서버와의 연결이 끊어졌는지 확인
  if (!client.connected()) {
    Serial.println("서버와의 연결이 끊어졌습니다.");
    client.stop();
    while (true);  // 연결이 끊어지면 멈춤
  }
}

// Wi-Fi 네트워크에 연결하는 함수
void connectToWiFi() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Wi-Fi에 연결 중... ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    delay(5000);  // 연결 대기
  }
  Serial.println("Wi-Fi에 연결되었습니다.");
  printWifiStatus();
}

// Wi-Fi 상태를 출력하는 함수
void printWifiStatus() {
  // IP 주소 출력
  IPAddress ip = WiFi.localIP();
  Serial.print("IP 주소: ");
  Serial.println(ip);
}
