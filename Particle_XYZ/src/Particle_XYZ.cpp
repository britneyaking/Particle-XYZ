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

SYSTEM_MODE(AUTOMATIC);

UDP udp;
Adafruit_BME280 bme;

// OSC Sending
IPAddress outIp(10, 75, 91, 78);//your computer IP
unsigned int outPort = 1234; //computer incoming port

// ULTRASONIC SENSOR
int DURATION;

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
Adafruit_MQTT_Publish mqtttempF = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/tempF");
Adafruit_MQTT_Publish mqttPa = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/pressPA");
Adafruit_MQTT_Publish mqttrhumidRH = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidRH");

unsigned int last, lastTime;

// BME 280
float tempC;
float pressPA;
float humidRH;

float tempF;
float Pa;


void setup() {

  // SERIAL
  Serial.begin(9600);

  bme.begin(0x76);

  udp.begin(0); //necessary even for sending only

  // Ultra Sonic Sensor 1
  pinMode(triggerPinSensor1, OUTPUT);
  pinMode(echoPinSensor1, INPUT);

 // Ultra Sonic Sensor 4
  pinMode(triggerPinSensor4, OUTPUT);
  pinMode(echoPinSensor4, INPUT);

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
  outMessage.send(udp,outIp,outPort);
  

// BME 280 TEMPERATURE
  tempC = bme.readTemperature();
  tempF = tempC*(9/5.0)+32;

// BME 280 PRESSURE
  pressPA = bme.readPressure();
  Pa = pressPA/3386;

// BME 280 HUMIDITY
  humidRH = bme.readHumidity();
 
  Serial.printf("TempF  %0.1f\n" , tempF);
  delay (100);
  Serial.printf("Pa  %0.1f\n" , Pa);
  delay (100);
  Serial.printf("humidRH  %0.1f\n" , humidRH);

//Adafruit Dashboard publish
 if (mqtt.Update())
    {
      mqtttempF.publish(tempF);
      Serial.printf("Publishing TempF %0.2f \n", tempF);
      mqttPa.publish(Pa);
      Serial.printf("Publishing Pa %0.2f \n", Pa);
      mqttrhumidRH.publish(humidRH);
      Serial.printf("Publishing humidityRH %0.2f \n", humidRH);
    }
    lastTime = millis();
  }

void MQTT_connect()
{
  int8_t ret;

  if (mqtt.connected())
  {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  while ((ret = mqtt.connect()) != 0)
  {
    Serial.printf("%s\n", (char *)mqtt.connectErrorString(ret));
    Serial.printf("Retrying MQTT connection in 5 seconds..\n");
    mqtt.disconnect();
    delay(5000);
  }
  Serial.printf("MQTT Connected!\n");
}
