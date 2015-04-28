#include <Servo.h>

const unsigned int MAX = 2;

Servo servos[MAX];

void setup() {                
  Serial.begin(9600);  
  
  for(int i = 0;i < MAX;++i){
    servos[i].attach(i + 3);
    servos[i].write(90);
  }
}

void loop() {
  
  for(int i = 0;Serial.available() > 0;++i){
    delay(1);    //速度小於1ms接收資料會錯誤
    int angle = Serial.read();
    servos[i].write(angle);
  }
}
