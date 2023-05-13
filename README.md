# Arduino_outsourcing
* 지인의 부탁으로 간단한 아두이노 작업 외주
* 초음파로 차를 감지하여 블루투스로 값을 다른 아두이노에게 보내 부저를 울리는 것 
* License - MIT
## 블루투스 연결 테스트
### AT 명령어
```
AT            : 연결 확인
AT+NAME????   : 이름 설정
AT+PIN????    : 핀번호 설정
AT+ROLE=M(S)  : 모드 설정 M-> Master S -> Slave
AT+RESET      : 모듈 재시작
```
### 마스터 코드
```
#include <SoftwareSerial.h>

int Tx = 7; // Tx Pin number
int Rx = 8; // Rx Pin number
SoftwareSerial BTSerial(Tx,Rx); // bluetooth 모듈 핀 설정

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // 시리얼 모니터 9600 보드레이트 통신선언
  BTSerial.begin(9600); // bluetooth 모듈 9600 보드레이트 통신선언
  Serial.println("Initialized"); // 모니터 출력
}

void loop() {
  // put your main code here, to run repeatedly:
  BTSerial.print("CONNECT");
  delay(1000);
}
```
![블루투스 기본설정](https://github.com/P-C-Space/Arduino_outsourcing/assets/39722575/6ac8df42-5687-4d4c-beb4-f7df20c159e4)
### 슬레이브 코드
```
#include <SoftwareSerial.h>

int Tx = 7; // Tx Pin number
int Rx = 8; // Rx Pin number
SoftwareSerial BTSerial(Tx,Rx); // bluetooth 모듈 핀 설정

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // 시리얼 모니터 9600 보드레이트 통신선언
  BTSerial.begin(9600); // bluetooth 모듈 9600 보드레이트 통신선언
  Serial.println("Initialized"); // 모니터 출력
}

void loop() {
  // put your main code here, to run repeatedly:
  if(BTSerial.available()){
    String text = BTSerial.readStringUntil(0x0D);

    Serial.println(text);
  }
}
```
![블루투스 slave설정](https://github.com/P-C-Space/Arduino_outsourcing/assets/39722575/41f4be51-db25-42e3-9d5a-45c7634b1bc6)
### 통신 테스트
![캡처](https://github.com/P-C-Space/Arduino_outsourcing/assets/39722575/ed443a98-4b0b-41a5-8503-6f3c1352db0f)
## 프로젝트
### 마스터 코드
```
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
```
### 마스터 코드
```
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
```
### 테스트 확인
https://github.com/P-C-Space/Arduino_outsourcing/assets/39722575/b6b8a716-74f3-4e60-9762-55c87666a9db
## 모듈 확인
* 초음파 센서 다루기 [이동](https://github.com/P-C-Space/Arduino_outsourcing/tree/main/%EC%B4%88%EC%9D%8C%ED%8C%8C)
* 부저 다루기 [이동](https://github.com/P-C-Space/Arduino_outsourcing/tree/main/%EB%B6%80%EC%A0%80)
* 블루투스 다루기 [이동](https://github.com/P-C-Space/Arduino_outsourcing/tree/main/%EB%B8%94%EB%A3%A8%ED%88%AC%EC%8A%A4)
