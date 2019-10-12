/*
  Reading a serial ASCII-encoded string.

  This sketch demonstrates the Serial parseInt() function.
  It looks for an ASCII string of comma-separated values.
  It parses them into ints, and uses those to fade an RGB LED.

  Circuit: 
  - Anode : Attach LED's Anode to PWM Pin : 9
  - Cathode: GND

  created 13 Apr 2012
  by Tom Igoe
  modified 14 Mar 2016
  by Arturo Guadalupi
  modified 12 Oct 2019
  by Sudhanshu Gupta
  
  This example code is in the public domain.
*/

// pins for the LEDs:
const int ledPin = 9;

void setup() {
  // initialize serial:
  Serial.begin(115200);
  // make the pins outputs:
  pinMode(ledPin, OUTPUT);
}

static int firstTime = 1;

void loop() {

  if(firstTime)
  {
	Serial.println("Enter RGB value : ");
	firstTime = 0;
  }
  
  // if there's any serial available, read it:
  while (Serial.available() > 0) {
	// look for the next valid integer in the incoming serial stream:
	int ledColorVal1 = Serial.parseInt();
	// do it again:
	int ledColorVal2 = Serial.parseInt();
	// do it again:
	int ledColorVal3 = Serial.parseInt();

	// look for the newline. That's the end of your sentence:
	if (Serial.read() == '\n') {
		// constrain the values to 0 - 255 and invert
		// if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
		ledColorVal1 = 255 - constrain(ledColorVal1, 0, 255);
		ledColorVal2 = 255 - constrain(ledColorVal2, 0, 255);
		ledColorVal3 = 255 - constrain(ledColorVal3, 0, 255);

		// Write to LED : as per the input received from user on serial port
		analogWrite(ledPin, ledColorVal1);
		delay(5000);

		analogWrite(ledPin, ledColorVal2);
		delay(5000);

		analogWrite(ledPin, ledColorVal3);
		delay(5000);	    

		// print the three numbers in one string as hexadecimal:
		Serial.print("LED Values written :  ");
		Serial.print(ledColorVal1, HEX); Serial.print(" ");
		Serial.print(ledColorVal2, HEX); Serial.print(" ");
		Serial.println(ledColorVal3, HEX);
	}
  }
}
