#include <Servo.h>

Servo horServo;
Servo verServo;
/*
I intentionally use the const byte construct here
instead of #define. It's less dangerous (no name collision possible)
and safer since variables have scope.
*/
const byte PUSH_BUTTON = 8;
const byte POT = A0;
const byte CMD_READ_POT = 1;
const byte CMD_READ_BTN = 2;
 
long prev_t = 0;
int potValue = 100;
byte cmd_id = 0; 
int verPos = 0;
 
byte btn_state = LOW;
 
String result="";
 
float getDistance(int v) {
  return 127.7*exp(-.01934*v)+37.48*exp(-.003001*v);
  //return 64.46 -.2768*v + .0003689*pow(v,2);
}
 
void setup() {
  //Setup input and outputs: LEDs out, pushbutton in.
  horServo.attach(11);
  verServo.attach(10);
  pinMode(PUSH_BUTTON, INPUT);
  Serial.begin(9600);
}
 
void loop() {
  byte btn_state = digitalRead(PUSH_BUTTON);
  //pot_value = analogRead(POT);
  //float dist = getDistance(pot_value);
  
  if(Serial.available() > 0) {
    cmd_id = Serial.read();
  } else {
    cmd_id = 0;
  }
  
  switch(cmd_id){
    case CMD_READ_POT:
      for (verPos = 0; verPos <= 90; verPos += 3) {
        verServo.write(verPos);
        for(int horPos = 0; horPos <= 90; horPos += 3){
          //Serial.println(horPos);
          potValue = analogRead(POT);
          float dist = getDistance(potValue);
          result = result + verPos + "," + horPos + "," + dist;
          Serial.println(result);
          result = "";
          horServo.write(horPos);
          delay(250);
        }
      }
//      result = result + "Potentiometer reads: " + pot_value + ", " + dist;
//      Serial.println(result);
//      result = "";
      break;
    case CMD_READ_BTN:
      result = result + "Button state: " + btn_state;
      Serial.println(result);
      result = "";
      break;
    break;
  }
}
