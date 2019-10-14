#include "Timer.h"

Timer t;
int pin = 13;

void setup()
{
  Serial.begin(115200);
  pinMode(pin, OUTPUT);
  t.oscillate(pin, 200, LOW);
  t.every(1000, takeReading, NULL);
}

void loop()
{
  t.update();
}

void takeReading(void * data)
{
  Serial.println(analogRead(0));
}
