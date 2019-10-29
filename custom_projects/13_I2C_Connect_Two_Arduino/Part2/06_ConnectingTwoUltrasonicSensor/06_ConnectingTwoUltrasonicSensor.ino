/*
  Dual HC-SR04 Demonstration
  
  Demonstrates enhancements of HC-SR04 Ultrasonic Range Finder
  Displays results on Serial Monitor

  DroneBot Workshop 2017
  http://dronebotworkshop.com
*/

// Include NewPing Library
#include "NewPing.h"

// Define Constants
#define TRIGGER_PIN_1   10
#define ECHO_PIN_1      10
#define TRIGGER_PIN_2   5
#define ECHO_PIN_2      5
#define MAX_DISTANCE    400

NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);

// Define Variables
float duration1; // Stores First HC-SR04 pulse duration value
float duration2; // Stores Second HC-SR04 pulse duration value
float distance1; // Stores calculated distance in cm for First Sensor
float distance2; // Stores calculated distance in cm for Second Sensor

int iterations = 5;

void setup() {
  Serial.begin (115200);
  Serial.println("Launching Firmware - Connect Two Ultrasonic Sensors (in 3-wire mode) on Pins 5 & 10 ");
}


void loop()
{
  delay(1000);

  // Measure duration for first sensor
  duration1 = sonar1.ping_median(iterations);
  
  // Add a delay between sensor readings
  delay(1000);
  
  // Measure duration for first sensor
  duration2 = sonar2.ping_median(iterations);

  // Calculate the distances for both sensors
  // Use 343 metres per second as speed of sound
  distance1 = (duration1 / 2) * 0.0343;
  distance2 = (duration2 / 2) * 0.0343;
  
  // Send results to Serial Monitor
  Serial.print("Distance 1: ");
  if (distance1 >= 400 || distance1 <= 2) {
    Serial.print("Out of range ");
  }
  else {
    Serial.print(distance1);
    Serial.print(" cm ");
  }
   
  Serial.print("Distance 2: ");

  if (distance2 >= 400 || distance2 <= 2) {
    Serial.print("Out of range ");
  }
  else {
    Serial.print(distance2);
    Serial.print(" cm");
  }
  
  Serial.println(" ");
}
