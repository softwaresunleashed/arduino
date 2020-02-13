// Include Arduino FreeRTOS library
#include <Arduino_FreeRTOS.h>
#include "defines.h"


/*******************************************************************************
 *******************************************************************************
 ********************************************************************************/
#if MOTOR_CONTROL_EN

#include <AFMotor.h>
#define INITIAL_SPEED     200
/*
      MOTOR CONTROL LOGIC
      ===================
*/
/*
Valid Values :
------------
Motor 1 & 2 : MOTOR12_64KHZ | MOTOR12_8KHZ  | MOTOR12_2KHZ  | MOTOR12_1KHZ
Motor 3 & 4 : MOTOR34_64KHZ | MOTOR34_8KHZ  |  ----------   | MOTOR34_1KHZ
*/
AF_DCMotor motor1(1, MOTOR12_1KHZ); // create motor #1, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_1KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor3(3, MOTOR34_1KHZ); // create motor #3, 64KHz pwm
AF_DCMotor motor4(4, MOTOR34_1KHZ); // create motor #4, 64KHz pwm

// Set Speed of Individual Motors
void setMotorSpeeds()
{
  // Valid speeds are between 0 to 255
  motor1.setSpeed( INITIAL_SPEED );     // set the speed to 200/255
  motor2.setSpeed( INITIAL_SPEED );     // set the speed to 200/255
  motor3.setSpeed( INITIAL_SPEED );     // set the speed to 200/255
  motor4.setSpeed( INITIAL_SPEED );     // set the speed to 200/255
}

void MotorControlThread(void *pvParameters)
{
#if SERIAL_EN  
  Serial.println("[MCL] Starting Motor Control Thread...");
#endif
  
	while(1)
	{
#if SERIAL_EN  
		Serial.println("[MCL] All Motors Forward...");
#endif
		    
	    // Go Forward
	    motor1.run( FORWARD );
	    motor2.run( FORWARD );
	    motor3.run( FORWARD );
	    motor4.run( FORWARD );
	    delay( THRD_DELAY * 100 );
		    
	    // Go Backward
#if SERIAL_EN  
		Serial.println("[MCL] All Motors Backward...");
#endif
		motor1.run( BACKWARD );
		motor2.run( BACKWARD );
		motor3.run( BACKWARD );
		motor4.run( BACKWARD );
		delay( THRD_DELAY * 100 );

	    // Stop motors
#if SERIAL_EN  
		Serial.println("[MCL] All Motors Halt...");
#endif
		motor1.run( RELEASE );
		motor2.run( RELEASE );
		motor3.run( RELEASE );
		motor4.run( RELEASE );
		delay(THRD_DELAY * 100);
	};
}

void initMotorControlThread()
{
#if SERIAL_EN
	Serial.print("Creating Motor Control Task...");
#endif

	xTaskCreate(MotorControlThread, "Motor Control Task", THREAD_STACK_SIZE, NULL, 1, NULL);

#if SERIAL_EN
	Serial.println("[Done]");
#endif  
}

#endif	/* MOTOR_CONTROL_EN */

/*******************************************************************************
 *******************************************************************************
 ********************************************************************************/
/*
      OLED Display Thread
      ===================
*/
#if OLED_SUPPORTED

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
	
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
	
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void DisplayWrite(String strMsg, int iRow, int iCol)
{
	/* Clear the buffer */
	display.clearDisplay();

	/* Normal 1:1 pixel scale */
	display.setTextSize(1);

	/* Draw white text */
	display.setTextColor(SSD1306_WHITE);

	/* Start at top-left corner */
	display.setCursor(iRow, iCol);

	/* Print msg */
	//display.println(F("Smart Car Boot Up"));
	display.println(strMsg.c_str());

	/* Upate display panel */
	display.display();
}

void initDisplayPanel()
{
	
#if OLED_SUPPORTED
	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
#if SERIAL_EN
		Serial.println(F("[Display] SSD1306 allocation failed"));
#endif
		return;
	} else {
#if SERIAL_EN
		Serial.println(F("[Display] Display Panel Initialized."));
#endif
	
		DisplayWrite(F("Smart Car"), 0, 0);
		DisplayWrite(F("DP Init"), 0, 1);
	}
#endif

}

void DisplayThread(void *pvParameters)
{
#if SERIAL_EN  
  Serial.println("[DisplayPanel] Starting Display Thread...");
#endif

	
  DisplayWrite(F("Thrd Running..."), 0, 2);

  while(1)
  {
#if SERIAL_EN  
	  Serial.println("[DisplayPanel] Thread Scheduled...");
#endif
	  
	/* TODO : Add Display Panel routines to display current status */

    delay(THRD_DELAY);
  }
}

void initDisplayThread()
{
#if SERIAL_EN
	Serial.print("Creating Display Task...");
#endif

	xTaskCreate(DisplayThread, "Display Thread", THREAD_STACK_SIZE, NULL, 1, NULL);

#if SERIAL_EN
	Serial.println("[Done]");
#endif  
}


#endif	/* OLED_SUPPORTED */


/*******************************************************************************
 *******************************************************************************
 ********************************************************************************/
/*
      User Input Thread
      =================
*/
void UserInputThread(void *pvParameters)
{
#if SERIAL_EN  
	  Serial.println("[UserInput] Starting User Input Thread...");
#endif
	  
  while(1)
  {
#if SERIAL_EN  
	Serial.println("[UserInput] Thread Scheduled...");
#endif

	/* TODO : Add User Input routines and act accordingly */


	delay(THRD_DELAY);
  };
}

void initUserInputThread()
{
#if SERIAL_EN
	Serial.print("Creating User Input Task...");
#endif

	xTaskCreate(UserInputThread, "User Input Thread", THREAD_STACK_SIZE, NULL, 1, NULL);

#if SERIAL_EN
	Serial.println("[Done]");
#endif  
}

/*******************************************************************************
 *******************************************************************************
 ********************************************************************************/
/*
	  Proximity Radar Thread
	  ======================
*/
void ProximityRadarThread(void *pvParameters)
{
#if SERIAL_EN  
	  Serial.println("[Proximity Radar] Starting Proxity Radar Thread...");
#endif
		  
	  while(1)
	  {
#if SERIAL_EN  
		Serial.println("[Proximity Radar] Thread Scheduled...");
#endif
		/* TODO : Add Proximity Sensor reading and acting */


		delay(THRD_DELAY);
	  };
	}

void initProximityRadarThread()
{
#if SERIAL_EN
	Serial.print("Creating Proximity Radar Task...");
#endif

	xTaskCreate(ProximityRadarThread, "Proximity Radar Thread", THREAD_STACK_SIZE, NULL, 1, NULL);

#if SERIAL_EN
	Serial.println("[Done]");
#endif  
}





/*******************************************************************************
 *******************************************************************************
 ********************************************************************************/
void createSystemThreads()
{
  initDisplayThread();
  initMotorControlThread();
  initUserInputThread();
  initProximityRadarThread();
}

void initUartComm()
{
  Serial.begin(BAUDRATE);           // set up Serial library at BAUDRATE bps
  while(!Serial);
}

void printWelcomeBanner()
{
#if SERIAL_EN
  Serial.println("Smart Car Booting Up...");
#endif    
}


void bootUpComplete()
{
#if SERIAL_EN
  Serial.println("Smart Car Boot Up...[DONE]");
#endif    
}

void setup()
{

  initUartComm();
  
  /* Print Welcome Banner */
  printWelcomeBanner();

  /* Do useful stuff here */
  /* .. */
  
  /* Boot up complete */
  bootUpComplete();
  
  /* Initialize Threads */
  createSystemThreads();  
}


/* We dont do anything here. 
	We have our own FreeRTOS threads */
void loop() { }
