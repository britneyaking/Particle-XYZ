/* 
 * Project: Particle XYZ
 * Author: Britney A. King
 * Date: 12-2-24
 */

#include "Particle.h"
#include "HC_SR04.h"

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);


// ULTRASONIC SENSOR
int DURATION;

// Ultra Sonic Sensor 1
const int triggerPinSensor1 = A5;
const int echoPinSensor1 = D3;
HC_SR04 UltrasonicSensor1 = HC_SR04(triggerPinSensor1, echoPinSensor1);
//HC_SR04 UltrasonicSensor1 = HC_SR04(triggerPinSensor1, echoPinSensor1, 10, 61);

int DISTANCE1;

// Ultra Sonic Sensor 4
const int triggerPinSensor4 = A0;
const int echoPinSensor4 = D6;
HC_SR04 UltrasonicSensor4 = HC_SR04(triggerPinSensor4, echoPinSensor4);
//HC_SR04 UltrasonicSensor4 = HC_SR04(triggerPinSensor4, echoPinSensor4, 123, 152);

int DISTANCE4;

//int DISTANCE1;

// Ultra Sonic Sensor 2
// const int triggerPinSensor2 = A2;
// const int echoPinSensor2 = D4;
// HC_SR04 UltrasonicSensor2 = HC_SR04(triggerPinSensor2, echoPinSensor2);
//HC_SR04 UltrasonicSensor2 = HC_SR04(triggerPinSensor2, echoPinSensor2, 62, 91);

//int DISTANCE2;

// Ultra Sonic Sensor 3
// const int triggerPinSensor3 = A1;
// const int echoPinSensor3 = D5;
// HC_SR04 UltrasonicSensor3 = HC_SR04(triggerPinSensor3, echoPinSensor3);
//HC_SR04 UltrasonicSensor3 = HC_SR04(triggerPinSensor3, echoPinSensor3, 92, 122);

//int DISTANCE3;


void setup() {

  // SERIAL
  Serial.begin(9600);

  // Ultra Sonic Sensor 1
  pinMode(triggerPinSensor1, OUTPUT);
  pinMode(echoPinSensor1, INPUT);

 // Ultra Sonic Sensor 4
  pinMode(triggerPinSensor4, OUTPUT);
  pinMode(echoPinSensor4, INPUT);


// Ultra Sonic Sensor 2
  // pinMode(triggerPinSensor2, OUTPUT);
  // pinMode(echoPinSensor2, INPUT);

 // Ultra Sonic Sensor 3
  // pinMode(triggerPinSensor3, OUTPUT);
  // pinMode(echoPinSensor3, INPUT);
}


void loop() {

  // Ultra Sonic Sensor 1
  digitalWrite(triggerPinSensor1,HIGH);
  delay(1);
  digitalWrite(triggerPinSensor1,LOW);
  DURATION = pulseIn(echoPinSensor1,HIGH);

  DISTANCE1 = DURATION / 58.2;
 
  if(DISTANCE1 > 0 && DISTANCE1 < 250 ){
    Serial.printf("%i \n", DISTANCE1);
    //    Serial.printf("%i /n", DISTANCE1);
    delay(100);
    }

  // Ultra Sonic Sensor 2
  // digitalWrite(triggerPinSensor2,HIGH);
  // delay(1);
  // digitalWrite(triggerPinSensor2,LOW);
  // DURATION = pulseIn(echoPinSensor2,HIGH);

  // DISTANCE2 = DURATION / 58.2;
 
  // if(DISTANCE2 > 0 && DISTANCE2 < 250 ){
  //   Serial.printf("Ultrasonic Sensor 2 %i \n", DISTANCE2);
  //   delay(100);
  //   }    

  // Ultra Sonic Sensor 3
  // digitalWrite(triggerPinSensor3,HIGH);
  // delay(1);
  // digitalWrite(triggerPinSensor3,LOW);
  // DURATION = pulseIn(echoPinSensor3,HIGH);

  // DISTANCE3 = DURATION / 58.2;
 
  // if(DISTANCE3 > 0 && DISTANCE3 < 250 ){
  //   Serial.printf("Ultrasonic Sensor 3 %i \n", DISTANCE3);
  //   delay(100);
  //   }  

  // Ultra Sonic Sensor 4
  digitalWrite(triggerPinSensor4,HIGH);
  delay(1);
  digitalWrite(triggerPinSensor4,LOW);
  DURATION = pulseIn(echoPinSensor4,HIGH);

  DISTANCE4 = DURATION / 58.2;
 
  if(DISTANCE4 > 0 && DISTANCE4 < 250 ){
    Serial.printf("%i \n", DISTANCE4);
   // delay(100);
    }  
}
