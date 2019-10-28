/*
 * Code : Driver for EEPROM 24C02 / 24C04
 *
 */
#include <stdlib.h>
#include <Wire.h>

#define DEBUG_ENABLE    1
#define SERIAL_BAUDRATE  115200
#define LOOP_DELAY  5000

#define MAX_I2C_WRITE   32  /* MAX I2C Write should be less than PAGE Size (to be on safer size) */
byte tempBuffer[MAX_I2C_WRITE];

byte zero = 0x00;

/* Supported EEPROM Types */
#define EEPROM_24C02	0x02
#define EEPROM_24C04	0x04

/* Compile for EEPROM IC define here */
#define EEPROM_TYPE		EEPROM_24C02
#if ( EEPROM_TYPE == EEPROM_24C02 )		/* 24C02 */

#define EEP_ADDR_MASK_MSB	0b01010000
#define A2		0b0 << 2	/* A2 should match the hardwired pin value */
#define A1		0b0 << 1	/* A1 should match the hardwired pin value */
#define A0		0b0 << 0	/* A0 should match the hardwired pin value */
/* 0b 0 0 0 0 A2 A1 A0 0 */
#define EEP_ADDR_MASK_LSB	( 0b00000000 | A2 | A1 | A0 )
#define EEPROM_ADDRESS 		( EEP_ADDR_MASK_MSB | EEP_ADDR_MASK_LSB )
#define EEPROM_SIZE_BYTES	256
#elif ( EEPROM_TYPE == EEPROM_24C04 )	/* 24C04 */
#define EEP_ADDR_MASK_MSB	0b01010000
#define A2		0b0 << 2	/* A2 should match the hardwired pin value */
#define A1		0b0 << 1	/* A1 should match the hardwired pin value */
#define A0		0b0 << 0	/* A0 Not connected */
/* 0b 0 0 0 0 A2 A1 x 0 */
#define EEP_ADDR_MASK_LSB	( 0b00000000 | A2 | A1 )
#define EEPROM_ADDRESS 		( EEP_ADDR_MASK_MSB | EEP_ADDR_MASK_LSB )
#define EEPROM_SIZE_BYTES	512
#endif


void writeToEEPROM()
{
	Wire.beginTransmission(EEPROM_ADDRESS);
	Wire.write(zero); //stop Oscillator

	Wire.write(zero); //start
	Wire.endTransmission();
}

uint8_t readFromEEPROM(uint16_t offset, uint8_t uiBytesToRead)
{
  uint8_t uiBytesRead = 0;

#if DEBUG_ENABLE
  Serial.print("Entered readFromEEPROM() ...Address = 0x");
  Serial.print(EEPROM_ADDRESS, HEX);
  Serial.print(" ");
#endif

	// Reset the register pointer
	Wire.beginTransmission(EEPROM_ADDRESS);
	Wire.write(zero);
	Wire.endTransmission();


//  uiBytesRead = Wire.requestFrom( ( int )EEPROM_ADDRESS, ( int )uiBytesToRead );
    Wire.requestFrom(( int )EEPROM_ADDRESS, MAX_I2C_WRITE, offset, uiBytesToRead, true);

#if DEBUG_ENABLE
  Serial.print("(");
  Serial.print(uiBytesRead);
  Serial.print(")");
  Serial.println("DONE.");
#endif

	return uiBytesRead;
}

String strBytesToRead = "";
String strOffset = "";
uint8_t uiBytesToRead = 0;
uint8_t uiBytesRead = 0;
uint16_t uiOffset = 0;

void setup () 
{
	/* Initialize I2C bus */
	Wire.begin();

	/* Initialize Serial bus */
	Serial.begin( SERIAL_BAUDRATE );
}

void loop () 
{
  delay(LOOP_DELAY);

  /* Number of bytes to read  */
  Serial.print("Enter Bytes to read from eeprom : ");
  while( Serial.available() == 0 ); // Wait for user input

  strBytesToRead = Serial.readString();
  Serial.println(strBytesToRead);

  /* Read Address */
  Serial.print("Enter Offset to read from : ");
  while( Serial.available() == 0 ); // Wait for user input

  strOffset = Serial.readString();
  Serial.println(strOffset);

#if DEBUG_ENABLE
  Serial.print("DUMPING BYTES (0x");
  uiBytesToRead = (unsigned int)strtoul(strBytesToRead.c_str(), NULL, DEC);
  uiOffset = (unsigned int)strtoul(strOffset.c_str(), NULL, DEC);
  Serial.print( uiBytesToRead, HEX );
  Serial.print(") FROM Offset (0x");
  Serial.print( uiOffset, HEX );
  Serial.println(")");
#endif

  readFromEEPROM( uiOffset, uiBytesToRead );
  Serial.print( "We Got this from Slave : " );
  while( Wire.available())
  {
    byte localByte = Wire.read();
    Serial.print( "0x" );
    Serial.print( localByte, HEX );
    Serial.print( " " );
  }
  Serial.println();
}
