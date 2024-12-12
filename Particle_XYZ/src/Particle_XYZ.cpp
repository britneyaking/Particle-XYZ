/* 
 * Project: Particle XYZ
 * Author: Britney A. King
 * Date: 12-2-24
 */

#include "Particle.h"
#include "HC_SR04.h"
#include "simple-OSC.h"
#include "Adafruit_BME280.h"
#include "credentials.h"
#include <Adafruit_MQTT.h>
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h"
#include "Adafruit_MQTT/Adafruit_MQTT.h"

SYSTEM_MODE(SEMI_AUTOMATIC);

UDP osc;

// OSC Sending
IPAddress outIp(10, 75, 91, 78);//your computer IP
unsigned int outPort = 1234; //computer incoming port

// ULTRASONIC SENSOR
int DURATION;

float UltraSonic1;
float UltraSonic4;

// Ultra Sonic Sensor 1
const int triggerPinSensor1 = A5;
const int echoPinSensor1 = D3;
HC_SR04 UltrasonicSensor1 = HC_SR04(triggerPinSensor1, echoPinSensor1);
int DISTANCE1;

// Ultra Sonic Sensor 4
const int triggerPinSensor4 = A0;
const int echoPinSensor4 = D6;
HC_SR04 UltrasonicSensor4 = HC_SR04(triggerPinSensor4, echoPinSensor4);
int DISTANCE4;

TCPClient TheClient;
Adafruit_MQTT_SPARK mqtt(&TheClient, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Setup Feeds to publish or subscribe
Adafruit_MQTT_Publish mqttUltraSonic1 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/UltraSonic1");
Adafruit_MQTT_Publish mqttUltraSonic4 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/UltraSonic4");

unsigned int last, lastTime;


void setup() {

  // SERIAL
  Serial.begin(9600);

  osc.beginPacket(outIp,outPort);
  osc.begin(outPort);

  // Ultra Sonic Sensor 1
  pinMode(triggerPinSensor1, OUTPUT);
  pinMode(echoPinSensor1, INPUT);

 // Ultra Sonic Sensor 4
  pinMode(triggerPinSensor4, OUTPUT);
  pinMode(echoPinSensor4, INPUT);
  
  WiFi.on();
  WiFi.connect();
  while (WiFi.connecting())
  {
    Serial.printf(".");
  }
}

void loop() {

  // Ultra Sonic Sensor 1
  digitalWrite(triggerPinSensor1,HIGH);
  delay(1);
  digitalWrite(triggerPinSensor1,LOW);
  DURATION = pulseIn(echoPinSensor1,HIGH);

  DISTANCE1 = DURATION / 30;
 
  if(DISTANCE1 > 0 && DISTANCE1 < 250 ){
    Serial.printf("%i \n", DISTANCE1);
    delay(100);
    }

  // Ultra Sonic Sensor 4
  digitalWrite(triggerPinSensor4,HIGH);
  delay(1);
  digitalWrite(triggerPinSensor4,LOW);
  DURATION = pulseIn(echoPinSensor4,HIGH);

  DISTANCE4 = DURATION / 30;
 
  if(DISTANCE4 > 0 && DISTANCE4 < 250 ){
    Serial.printf("%i \n", DISTANCE4);
    }  

//OSC Sending ULTRA SONIC 1
  OSCMessage outMessage("/ULTRA SONIC 1");
  outMessage.addInt(DISTANCE1);
  outMessage.send(osc,outIp,outPort);

//OSC Sending ULTRA SONIC 2
  OSCMessage outMessage2 ("/ULTRA SONIC 2");
  outMessage.addInt(DISTANCE4);
  outMessage.send(osc,outIp,outPort);

//Adafruit Dashboard publish
 UltraSonic1 = DISTANCE1;

  if (mqtt.Update())
    {
      mqttUltraSonic1.publish(UltraSonic1);
       Serial.printf("Publishing UltraSonic1 %i \n", UltraSonic1);
     }
     lastTime = millis();

 UltraSonic4 = DISTANCE4;

  if (mqtt.Update())
    {
      mqttUltraSonic4.publish(UltraSonic4);
       Serial.printf("Publishing UltraSonic4 %i \n", UltraSonic4);
     }
     lastTime = millis();
}
