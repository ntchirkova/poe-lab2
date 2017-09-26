#include <Servo.h>

Servo horServo;
Servo verServo;

const byte POT = A0;
int horPos = 0;
int verPos = 0;
int potValue = 0;
String result = "";
int go = 0;

void setup() {
  horServo.attach(11);
  verServo.attach(10);
  Serial.begin(9600);
}

void loop() {
  //if (Serial.available() > 0) {
    //go = Serial.read(); //subtract ASCII value of '0'
  //}
  //if (go == 1) {
    //    for (verPos = 0; verPos <= 100; verPos += 1) {
    for(horPos = 0; horPos <= 100; horPos++){
      //Serial.println(horPos);
      potValue = analogRead(POT);
      float dist = getDistance(potValue);
      result = result + verPos + "," + horPos + "," + dist;
      Serial.println(result);
      result = "";
      horServo.write(horPos);
    }
    Serial.println("0,0,0");
    //   }
  //}
}

float getDistance(int v) {
  return 64.46 - .2768 * v + .0003689 * pow(v, 2);
}
