/*
 * SmartCarCpp.cpp
 *
 * Created: 11/24/2019 7:59:33 AM
 * Author : nxf29631
 */ 


#include <avr/io.h>
#include <stdio.h>

#include "Arduino.h"
#include "pins_arduino.h"

#include "port.h"
#include "defines.h"
#include "OledDisplay.h"

void setup()
{
	OledDisplay::OledTaskInit();
	
	// initialize digital pin LED_BUILTIN as an output.
	//pinMode(LED_BUILTIN, OUTPUT);

}

void loop()
{
	/* Replace with your application code */
	while (1)
	{
		//digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
		//delay(1000);                       // wait for a second
		//digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
		//delay(1000);                       // wait for a second		
	};
}

/* Behold...And Now.....Let the Magic Begin ;) */
int main(void)
{
	setup();

#if 0	
	loop();
#endif
}

