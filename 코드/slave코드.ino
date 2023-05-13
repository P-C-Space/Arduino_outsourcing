#include <SoftwareSerial.h>

int Tx = 7; // Tx Pin number
int Rx = 8; // Rx Pin number
SoftwareSerial BTSerial(Tx,Rx); // bluetooth 모듈 핀 설정

int buzzerPin = 4; // 능동부저 핀번호
char text; // 변수명 초기화

unsigned int check_time;

void setup() {
  // put your setup code here, to run once:
  // 아두이노 시작 한번만 실행
  Serial.begin(9600); // 시리얼 모니터 9600 보드레이트 통신선언
  BTSerial.begin(9600); // bluetooth 모듈 9600 보드레이트 통신선언
  
  pinMode(buzzerPin, OUTPUT); // 능동부저 출력값으로 설정
}

void loop() {
  // 반복적으로 실행
  // put your main code here, to run repeatedly:
  if(BTSerial.available()){ // 만약 값이 있다면
    text = BTSerial.read(); // 값 text라는 문자열 변수에 저장
    Serial.print(text);
  }


  if(text == '1'){ // 1 이면 부저 출력
    digitalWrite(buzzerPin, HIGH); // 부저 출력
    delay(2500);
  }
  else{
    digitalWrite(buzzerPin, LOW); // 부저 종료
  }
  
}
