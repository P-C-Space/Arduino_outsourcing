
int buzzerPin = 7; // 능동부저 핀번호

void setup() {
  // put your setup code here, to run once:
  // 아두이노 시작 한번만 실행
  pinMode(buzzerPin, OUTPUT); // 능동부저 출력값으로 설정
  
}

void loop() {
  // 반복적으로 실행
  // put your main code here, to run repeatedly:

  // 1.5초 울리고 끄는 부저
  digitalWrite(buzzerPin, HIGH); // 부저 출력
  delay(1500);

  digitalWrite(buzzerPin, LOW); // 부저 종료 
  delay(3000);

  
}
