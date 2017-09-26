#include <Servo.h>

// Initializes each of the Servo variables
Servo horServo;
Servo verServo;

const byte POT = A0; // Port of where the IR scanner is attached
const byte CMD_READ_POT = 1; // Constant for switch statement

int potValue = 100; // Initializes a value for the IR Scan
byte cmd_id = 0; // Initializes a value for variable that reads from Python Script
int verPos = 0;
 
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
      for (verPos = 0; verPos <= 90; verPos += 3) {
        verServo.write(verPos);
        for(int horPos = 0; horPos <= 90; horPos += 3){
          potValue = analogRead(POT);
          float dist = getDistance(potValue);
          result = result + verPos + "," + horPos + "," + dist;
          Serial.println(result);
          result = "";
          horServo.write(horPos);
          delay(250);
        }
      }
      break;
    break;
  }
}
