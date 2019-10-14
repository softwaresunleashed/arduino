

#include "Timer.h"
Timer t;
int pin = 13;

void setup()
{
  pinMode(pin, OUTPUT);

  // pulse() takes the pin number to toggle 
  // and every "5*1000" time interval
  t.pulse(pin, 5 * 1000, HIGH); // 5 secs
}

void loop()
{
  t.update();
}
