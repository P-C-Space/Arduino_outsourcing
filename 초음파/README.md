# 초음파 다루기
* 이 작업에서 사용하는 초음파 센서는 약 40KHz, 4~5m의 거리를 측정하며 trig에서 음파를 발사하고, echo로 받는 초음파 거리센서입니다.
## 하드웨어 연결
![캡처](https://github.com/P-C-Space/Arduino_outsourcing/assets/39722575/6a6e16da-9372-4b47-adae-e1ac8bb61cee)

## 코드
```
int trigPin = 4; // 초음파 센서 trig핀 digital 4번
int echoPin = 5; // 초음파 센서 echo핀 digital 5번

void setup() {
  // put your setup code here, to run once:
  // 아두이노 실행시 처음 한번만 실행
  Serial.begin(9600);
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

  Serial.print("Duration: "); // duration 출력
  Serial.print(duration);
  Serial.print("\nDistance : "); // distance 거리 출력
  Serial.print(distance);
  Serial.println("cm\n");

   
  delay(3000); // 3초 정지
}
```

## 시리얼 모니터 출력 
![초음파센서 시리얼](https://github.com/P-C-Space/BaekHub/assets/39722575/99ce6efa-04fb-4b2c-bc8e-f0b0196947ac)
