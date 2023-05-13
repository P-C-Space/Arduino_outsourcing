#include <SoftwareSerial.h>

int Tx = 7; // Tx Pin number
int Rx = 8; // Rx pin number

SoftwareSerial btserial(Tx,Rx); // bluetooth 모듈 핀 설정

int trigPin = 4; // 초음파 센서 trig핀 digital 4번
int echoPin = 5; // 초음파 센서 echo핀 digital 5번

void setup() {
  // put your setup code here, to run once:
  // 아두이노 실행시 처음 한번만 실행
  btserial.begin(9600); // 블루투스 연결
  
  Serial.begin(9600); // 시리얼 모니터 연결
  pinMode(trigPin,OUTPUT);  // 신호를 보내는 trig핀 => OUTPUT
  pinMode(echoPin,INPUT);   // 신호를 받는 echo핀 => INPUT
}

void loop() {
  // put your main code here, to run repeatedly:
  // 이후 반복적으로 실행하는 구간
  float duration,distance; // 변수 선언

  digitalWrite(trigPin,HIGH); // 초음파 출력
  delay(10); // 0.01초 만큼 정지
  digitalWrite(trigPin,LOW); // 초음파 출력 중지
  
  duration = pulseIn(echoPin,HIGH); // echo가 HIGH인 시간
  // HIGH일 때 초음파를 보내고 돌아오는 시간을 계산 
  // 340은 초당 소리의 속도 
  // 10000은 밀리세컨드 => 세컨드
  // 왕복거리이므로 2로 나눔
  distance = ((float)(340*duration) / 10000) / 2;

  if(distance <= 10){ // 수치 설정 10 => 10cm 방에서 테스트하기 위해서 10cm설정
    // 일정 값 아래의 거리이면
    btserial.print('1'); // 1 => 물체가 있다.
    delay(3000);
  }
  else{
    btserial.print('0');
  }



// 출력 확인
  Serial.print("Duration: "); // duration 출력
  Serial.print(duration);
  Serial.print("\nDistance : "); // distance 거리 출력
  Serial.print(distance);
  Serial.println("cm\n");

  delay(100);
}
