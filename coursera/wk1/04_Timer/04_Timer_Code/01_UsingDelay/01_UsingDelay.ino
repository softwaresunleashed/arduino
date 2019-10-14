int pin = 13;

void setup()
{
  pinMode(13, OUTPUT);
}

void loop()
{
  digitalWrite(pin, HIGH);
  delay(5 * 1000);
  digitalWrite(pin, LOW);
  delay(5 * 1000);
}
