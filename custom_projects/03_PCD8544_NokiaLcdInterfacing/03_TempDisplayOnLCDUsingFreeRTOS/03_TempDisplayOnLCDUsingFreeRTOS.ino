
/* Include Arduino FreeRTOS library */
#include <Arduino_FreeRTOS.h>

/* LCD Include file */
#include <PCD8544.h>

/* Code for reading from Temperature Sensor */ 
#include <OneWire.h>
#include <DallasTemperature.h>

#define THREAD_DELAY	5000

/* Wiring Details */
/* PIN definition for LCD on Arduino board */
#define SCLK_PIN  3   // Clock pin
#define DIN_PIN   4   // Data In pin
#define DC_PIN    5   // Data/Command select pin 
#define RST_PIN   6   // LCD reset pin
#define SCE_PIN   7   // Select Chip Enable pin

/* Data wire is plugged into pin 8 on Ardiuno */
#define ONE_WIRE_BUS 8

/* Global variables */
float fCurrentTemp = 0;

void setup()
{
	
	/* Create LCD FreeRTOS thread */
	xTaskCreate(LCDDisplayTask, "LCD Display Thread", 128, NULL, 1, NULL);
  
	/* Create Temperature FreeRTOS thread */
	xTaskCreate(TempReadTask, "Temp Read Task", 128, NULL, 1, NULL);
}


// Loop is empty in case of FreeRTOS, we have our own threads now.
void loop() {  }

/* ------------------ LCD related stuff ---------------------*/
/* Create an object with LCD pins as defined above */
PCD8544 lcd(SCLK_PIN, DIN_PIN, DC_PIN, RST_PIN, SCE_PIN);

#define LCD_WIDTH     84
#define LCD_HEIGHT    48

void LCDDisplayTask(void *pvParameters)
{
	lcd.begin(LCD_WIDTH, LCD_HEIGHT);

	while(1)
	{
		lcd.setCursor(0, 0);
		lcd.print("Temp : ");

		lcd.setCursor(0, 1);
		/* Print current temperature that is read in another thread */
		lcd.print(fCurrentTemp);
		lcd.print(" C");

		lcd.setCursor(0, 5);
		lcd.print("Auth:Sudhanshu");

		delay(THREAD_DELAY);
	}
}


/* ------------------ Temp IC related stuff ---------------------*/

/*
	Setup a oneWire instance to communicate with any OneWire 
	devices (not just lcMaxim/Dallas temperature ICs)
*/ 
OneWire oneWire(ONE_WIRE_BUS);

/* Pass our oneWire reference to Dallas Temperature. */
DallasTemperature sensors(&oneWire);


void TempReadTask(void *pvParameters)
{
  // start serial port
  Serial.begin(115200);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
  
  while(1)
  {
    // Send the command to get temperatures
	  sensors.requestTemperatures();
	
	  // Read temperature from IC
	  fCurrentTemp = sensors.getTempCByIndex(0);

    Serial.print("Temperature for Device 1 is: ");
    Serial.print(sensors.getTempCByIndex(0)); 
  
	  delay(THREAD_DELAY);
  }
}
