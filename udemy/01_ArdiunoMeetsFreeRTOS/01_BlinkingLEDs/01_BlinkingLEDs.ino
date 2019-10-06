/*
  Blinking LEDs Demo using digitialWrite() 

  The circuit:
  - Connect 3 LEDs to digital pins & GND with 100ohm resistors in series.
  

  created 06 Oct 2019
  by Sudhanshu Gupta

  This example code is in the public domain.

*/

#define RED     6
#define BLUE    7
#define YELLOW  8

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);
}

void loop() {
  digitalWrite(RED, digitalRead(RED)^1);
  digitalWrite(BLUE, digitalRead(BLUE)^1);
  digitalWrite(YELLOW, digitalRead(YELLOW)^1);
  delay(500);
}
