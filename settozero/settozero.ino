#include <Servo.h>

Servo horServo;
Servo verServo;
void setup() {
  // put your setup code here, to run once:
  horServo.attach(11);
  verServo.attach(10);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  verServo.write(0);
  horServo.write(0);
}
