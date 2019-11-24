/*
 * OledDisplay.c
 *
 * Created: 11/23/2019 8:45:38 PM
 *  Author: nxf29631
 */ 

#include "OledDisplay.h"

#if OLED_EN_128_32

#include "OledDisplayTask.h"
#include "port.h"
#include "defines.h"
#include "USBAPI.h"
//#include "HardwareSerial.h"


#include <Arduino_FreeRTOS.h>

extern void OLEDDisplayTask(void *pvParameters);

void OledDisplay::OledTaskInit()
{
	
#if SERIAL_EN
	Serial.print("Starting OLEDDisplay Task...");
#endif

	/* Create LCD FreeRTOS thread */
	xTaskCreate(OLEDDisplayTask, "OLED Display Thread", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

#if SERIAL_EN
	Serial.println("DONE.");
#endif
}



#endif	/* #if OLED_EN_128_32 */