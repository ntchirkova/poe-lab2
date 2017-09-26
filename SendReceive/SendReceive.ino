#include <Servo.h>

Servo horServo;
Servo verServo;

const byte POT = A0;
const byte CMD_READ_POT = 1;
const byte CMD_READ_BTN = 2;
 
int potValue = 100;
byte cmd_id = 0; 
 
byte btn_state = LOW;
 
String result="";
 
float getDistance(int v) {
  return 127.7*exp(-.01934*v)+37.48*exp(-.003001*v);
  //return 64.46 -.2768*v + .0003689*pow(v,2);
}
 
void setup() {
  horServo.attach(11);
  verServo.attach(10);
  Serial.begin(9600);
}
 
void loop() {
  if(Serial.available() > 0) {
    cmd_id = Serial.read();
  } else {
    cmd_id = 0;
  }
  
  switch(cmd_id){
    case CMD_READ_POT:
      for(int horPos = 0; horPos <= 90; horPos++){
        potValue = analogRead(POT);
        float dist = getDistance(potValue);
        result = result + verPos + "," + horPos + "," + dist;
        Serial.println(result);
        result = "";
        horServo.write(horPos);
        delay(250);
      }
      break;
    case CMD_READ_BTN:
      result = result + "Button state: " + btn_state;
      Serial.println(result);
      result = "";
      break;
    break;
  }
}
