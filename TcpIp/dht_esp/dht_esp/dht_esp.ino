//온습도 센서 + esp -> strtok해보기
#include <WiFiEsp.h>
#include <SoftwareSerial.h>
#include <SimpleDHT.h>

// 소프트웨어 직렬 포트를 통해 ESP8266과 통신
SoftwareSerial Serial1(10, 11); // RX, TX

// Wi-Fi 네트워크 정보
char ssid[] = "test01";        // Wi-Fi 네트워크 이름
char pass[] = "12341234";    // Wi-Fi 비밀번호

// 리눅스 채팅 서버 정보
char server_ip[] = "192.168.0.4";  // 리눅스 서버 IP 주소
int server_port = 9100;              // 리눅스 서버 포트 번호

WiFiEspClient client;  // Wi-Fi 클라이언트 객체

// 온습도센서 핀, 객체선언, 보낼 메세
#define DHT_PIN 2
SimpleDHT11 dht11;
char msg[7] = {0};

void setup() {
  // put your setup code here, to run once:
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
  // put your main code here, to run repeatedly:
  byte temp, humi;
  int err = SimpleDHTErrSuccess;

  dht11.read(DHT_PIN, &humi, &temp, NULL);
  sprintf(msg, "%d:%dL", (int)humi, (int)temp);

  Serial.println("보낸 값 : ")
  client.write(msg);
  Serial.println(msg);
  delay(1000);


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

