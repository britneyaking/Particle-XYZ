/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 */

#include "Particle.h"

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);

int delay_time = 40; // delay for this amount each write cycle. 
byte MIDI_channel = 1;
byte cc_number = 127;

byte printing_byte = 0;
int baud_rate = 31250;

const int triggerPinSensor1 = A5;
const int echoPinSensor1 = D3;

int val = 0;
int ultrasoundValue = 0;

int timecount = 0; // Echo counter
int ledPin = 13; // LED connected to digital pin 13


void setup() {

Serial.begin(baud_rate);

  pinMode(triggerPinSensor1, OUTPUT);
  pinMode(echoPinSensor1, INPUT);

  MIDI_channel = MIDI_channel - 1;

}

void loop() {

  timecount = 0;
  val = 0;

  // Ultra Sonic Sensor 1
  digitalWrite(triggerPinSensor1,HIGH);
  delay(1);
  digitalWrite(triggerPinSensor1,LOW);
  DURATION = pulseIn(echoPinSensor1,HIGH);

  DISTANCE1 = DURATION / 58.2;

  // Send low-high-low pulse to activate the trigger pulse of the sensor

  digitalWrite(ultraSoundSignal, LOW); // Send low pulse
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(ultraSoundSignal, HIGH); // Send high pulse
  delayMicroseconds(5); // Wait for 5 microseconds
  digitalWrite(ultraSoundSignal, LOW); // Holdoff

  // Listening for echo pulse

  pinMode(ultraSoundSignal, INPUT); // Switch signalpin to input
  val = digitalRead(ultraSoundSignal); // Append signal value to val
  while(val == LOW) { // Loop until pin reads a high value
    val = digitalRead(ultraSoundSignal);
  }

  while(val == HIGH) { // Loop until pin reads a high value
    val = digitalRead(ultraSoundSignal);
    timecount = timecount +1;            // Count echo pulse time
  }

  ultrasoundValue = timecount; // Append echo pulse time to ultrasoundValue

  /* BEGIN EDITED CODE */

  ultrasoundValue = ultrasoundValue - 14; 
  ultrasoundValue = ultrasoundValue / 5;

  if(ultrasoundValue > 127) {
    printing_byte = 127;
  }
  
  else {
  
  printing_byte = ultrasoundValue;
  }
  
  printByte(B10110000 + MIDI_channel);
  printByte(cc_number);
  printByte(printing_byte);


}


