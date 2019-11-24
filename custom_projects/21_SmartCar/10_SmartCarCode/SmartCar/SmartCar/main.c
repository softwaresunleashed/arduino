/*
 * SmartCar.c
 *
 * Created: 11/23/2019 9:18:50 PM
 * Author : nxf29631
 */ 


#include <avr/io.h>
#include <stdio.h>

#include "port.h"
#include "defines.h"
#include "OledDisplay.h"


void setup()
{
	OledTaskInit();
}

void loop()
{
	/* Replace with your application code */
	while (1)
	{
	};
}


/* Behold...And Now.....Let the Magic Begin ;) */
int main(void)
{
	setup();
	
	loop();
}

