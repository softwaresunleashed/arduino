/*
  Ardiuno Meets FreeRTOS

  This tutorial ports FreeRTOS to Ardiuno environment. 
  Use FreeRTOS’s thread functionality to blink 3 LEDs connected 
  to digitial input pins. (Instead of using single thread environment 
  of Ardiuno’s loop() function.


  The circuit:
  - Connect 3 LEDs to digital pins & GND with 100ohm resistors in series.
  

  created 06 Oct 2019
  by Sudhanshu Gupta

  This example code is in the public domain.

*/

// Include Arduino FreeRTOS library
#include <Arduino_FreeRTOS.h>

#define RED     6
#define BLUE    7
#define YELLOW  8

void setup() {
  
  // Create FreeRTOS threads
  xTaskCreate(redLedControllerTask, "RED LED Task", 128, NULL, 1, NULL);
  xTaskCreate(blueLedControllerTask, "BLUE LED Task", 128, NULL, 1, NULL);
  xTaskCreate(yellowLedControllerTask, "YELLOW LED Task", 128, NULL, 1, NULL);
}

void redLedControllerTask(void *pvParameters)
{
  pinMode(RED, OUTPUT);
  while(1)
  {
    digitalWrite(RED, digitalRead(RED)^1);    // XOR toggles LED ON / OFF
    delay(5000);
  }
}

void blueLedControllerTask(void *pvParameters)
{
  pinMode(BLUE, OUTPUT);
  while(1)
  {
    digitalWrite(BLUE, digitalRead(BLUE)^1);    // XOR toggles LED ON / OFF
    delay(5000);
  }
}

void yellowLedControllerTask(void *pvParameters)
{
  pinMode(YELLOW, OUTPUT);
  while(1)
  {
    digitalWrite(YELLOW, digitalRead(YELLOW)^1); // XOR toggles LED ON / OFF
    delay(5000);  
  }
}

// Loop is empty in case of FreeRTOS, we have our own threads now.
void loop() {  }
