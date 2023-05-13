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
