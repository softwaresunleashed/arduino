/*
 * OledDisplayTask.c
 *
 * Created: 11/24/2019 5:55:30 PM
 *  Author: nxf29631
 */ 


void OLEDDisplayTask(void *pvParameters)
{
	#if SERIAL_EN
	Serial.println("OLED Thread Started...");
	#endif

	// initialize digital pin LED_BUILTIN as an output.
	pinMode(LED_BUILTIN, OUTPUT);

	while(1)
	{
		digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
		delay(1000);                       // wait for a second
		digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
		delay(1000);                       // wait for a second
	};
}
