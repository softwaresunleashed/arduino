
/* Include Arduino FreeRTOS library */
#include <Arduino_FreeRTOS.h>

/* Configurable Parameters of program */
#define MMC_EN  1
#define TEMP_EN 1
#define LCD_EN  0
#define SERIAL_EN 1

/* FreeRTOS Config Params */
#define configMINIMALSTACKSIZE  ( ( unsigned short ) 128)


#if LCD_EN
/* LCD Include file */
#include <PCD8544.h>
#endif

#if TEMP_EN
/* Code for reading from Temperature Sensor */ 
#include <OneWire.h>
#include <DallasTemperature.h>
#endif

#if MMC_EN
/* MMC card logging related headers */
#include <SPI.h>
#include <SD.h>
#endif

#define THREAD_DELAY  6000


/* ------------ Wiring Details ------------ */
#if LCD_EN
/* PIN definition for LCD on Arduino board */
#define SCLK_PIN  3   // Clock pin
#define DIN_PIN   4   // Data In pin
#define DC_PIN    5   // Data/Command select pin 
#define RST_PIN   6   // LCD reset pin
#define SCE_PIN   7   // Select Chip Enable pin
#endif

#if TEMP_EN
/* Data wire is plugged into pin 8 on Ardiuno */
#define ONE_WIRE_BUS 8
#endif

#if MMC_EN
/* SD card connection */
/*  The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 2
 */
#define MMC_MOSI  11
#define MMC_MISO	12
#define MMC_CLK		13
#define MMC_CS		10
#endif


/* ------------ Global variables ------------ */
float fCurrentTemp = 0;		// Keep tab on temperature


void setup()
{
	// Open serial communications and wait for port to open:
#if SERIAL_EN
	Serial.begin(115200);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}
#endif 

#if MMC_EN
  mmcInit();
#endif

#if LCD_EN
#if SERIAL_EN
  Serial.print("Creating LCD Task...");
#endif  
	/* Create LCD FreeRTOS thread */
	xTaskCreate(LCDDisplayTask, "LCD Display Thread", configMINIMALSTACKSIZE, NULL, 1, NULL);
#if SERIAL_EN
  Serial.println("DONE.");
#endif  
#endif  /* LCD_EN */

#if TEMP_EN
#if SERIAL_EN  
	Serial.print("Creating Temperature Task...");
#endif 
  /* Create Temperature FreeRTOS thread */
	xTaskCreate(TempReadTask, "Temp Read Task", configMINIMALSTACKSIZE, NULL, 1, NULL);
#if SERIAL_EN  
  Serial.println("DONE.");
#endif
#endif  /* TEMP_EN */

}

// Loop is empty in case of FreeRTOS, we have our own threads now.
void loop() {  }

#if MMC_EN
/* ------------------ MMC Logging related stuff ---------------------*/
#define MMC_TEMP_FILENAME	"TempLogger.txt"
File myFile;        // Handle to file for MMC logging

void mmcInit()
{
#if SERIAL_EN  
  Serial.print("[mmc] Initializing SD card...");
#endif  
  if (!SD.begin( MMC_CS )) {
#if SERIAL_EN    
    Serial.println("SD init failed!");
#endif    
    while (1);
  }

#if SERIAL_EN  
  Serial.println("SD init done.");
#endif
  
}

void mmcWrite(float fTemperature)
{
		// open the file. note that only one file can be open at a time,
		// so you have to close this one before opening another.
		myFile = SD.open(MMC_TEMP_FILENAME, FILE_WRITE);

		// if the file opened okay, write to it:
		if (myFile) {
			// write to mmc card
#if SERIAL_ENABLE
      Serial.print("[mmc] Writing Temperature :");
      Serial.println(fCurrentTemp);
#endif
			myFile.println(fCurrentTemp);
			
			// close the file
			myFile.close();
		} else {
			// if the file didn't open, print an error:
#if SERIAL_EN     
			Serial.println("[mmc] Error opening mmc file");
#endif     
		}
}
#endif


#if LCD_EN
/* ------------------ LCD related stuff ---------------------*/
/* Create an object with LCD pins as defined above */
PCD8544 lcd(SCLK_PIN, DIN_PIN, DC_PIN, RST_PIN, SCE_PIN);

#define LCD_WIDTH     84
#define LCD_HEIGHT    48

void LCDDisplayTask(void *pvParameters)
{
#if SERIAL_EN
	Serial.println("LCD Thread Started...");
#endif  
	lcd.begin(LCD_WIDTH, LCD_HEIGHT);

	while(1)
	{
		/* Wait for Mailbox..If received display temperature on LCD */
		/* TODO: Add wait api here */
		
		
		lcd.setCursor(0, 0);
		lcd.print("Temp : ");

		lcd.setCursor(0, 1);
		/* Print current temperature that is read in another thread */
		lcd.print(fCurrentTemp);
		lcd.print(" C");

#if SERIAL_EN
    Serial.print("[lcd] LCD Temp Display :");
    Serial.println(fCurrentTemp);
#endif

		lcd.setCursor(0, 5);
		lcd.print("Auth:Sudhanshu");

		delay(THREAD_DELAY);
	}
}
#endif

#if TEMP_EN
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
#if SERIAL_EN
	Serial.println("Temp Thread Started...");
#endif

	// Start up the library
	sensors.begin();
  
	while(1)
	{
		// Send the command to get temperatures
		sensors.requestTemperatures();

		// Read temperature from IC
		fCurrentTemp = sensors.getTempCByIndex(0);

#if SERIAL_EN
		Serial.print("[temp] Temperature for Device 1 is: ");
		Serial.println(fCurrentTemp); 
#endif

#if MMC_EN
    // Write to MMC Card
    mmcWrite( fCurrentTemp );
#endif

		delay(THREAD_DELAY);
	}
}
#endif
