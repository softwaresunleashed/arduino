/* 
 * EEPROM (Internal) Read / Write Code 
 * 
 * The Code Reads (and dumps on serial port) Initial values 
 * of EEPROM (Internal), then Writes Values 0x00xx to Address (0xabxx)
 * 
 * PS : Only the LSByte of Address is written to address of EEPROM. 
 * Remember each Address is 8bit / 1 byte long....right ;)
 * 
 * Author : Sudhanshu Gupta
 * Email : cool.sudhanshu@gmail.com
 * Date : 26 Oct 2016
 */
#include <EEPROM.h>

#define SERIAL_BAUDRATE  115200

#define READ_ENABLE		1	/* Enable to Read from Internal EEPROM */
#define WRITE_ENABLE	1	/* Enable to Write to Internal EEPROM */

#if READ_ENABLE
void ReadInternalEEPROM()
{
	// start reading from the first byte (address 0) of the EEPROM
	int address = 0;
	byte value = 0;

	Serial.println("Reading from internal EEPROM : ");
	while(1)
	{
		// read a byte from the current address of the EEPROM
		value = EEPROM.read(address);

		Serial.print("Read Value (0x");
		Serial.print(value, HEX);
		Serial.print(") from Address (0x");
		Serial.print(address, HEX);
		Serial.println(")");

		/***
		Advance to the next address, when at the end restart at the beginning.

		Larger AVR processors have larger EEPROM sizes, E.g:
		- Arduno Duemilanove: 512b EEPROM storage.
		- Arduino Uno:        1kb EEPROM storage.
		- Arduino Mega:       4kb EEPROM storage.

		Rather than hard-coding the length, you should use the pre-provided length function.
		This will make your code portable to all AVR processors.
		***/
		address = address + 1;
		if (address == EEPROM.length()) {
			address = 0;
			break;
		}

		/***
		As the EEPROM sizes are powers of two, wrapping (preventing overflow) of an
		EEPROM address is also doable by a bitwise and of the length - 1.

		++address &= EEPROM.length() - 1;
		***/	
	}
}
#endif

#if WRITE_ENABLE
void WriteInternalEEPROM()
{
	// start reading from the first byte (address 0) of the EEPROM
	int address = 0;
	byte value = 0;

	Serial.println("Writing to Internal EEPROM : ");
	while(1)
	{
	   /***
		Write the value to the appropriate byte of the EEPROM.
		these values will remain there when the board is
		turned off.
	  ***/
	  Serial.print("Writing Value (0x");
	  Serial.print(value, HEX);
	  Serial.print(") at Address (0x");
	  Serial.print(address, HEX);
	  Serial.println(")");
	  
	  EEPROM.write(address, value);

	  /***
		Advance to the next address, when at the end restart at the beginning.

		Larger AVR processors have larger EEPROM sizes, E.g:
		- Arduno Duemilanove: 512b EEPROM storage.
		- Arduino Uno:        1kb EEPROM storage.
		- Arduino Mega:       4kb EEPROM storage.

		Rather than hard-coding the length, you should use the pre-provided length function.
		This will make your code portable to all AVR processors.
	  ***/
	  value = address = address + 1;
	  if (address == EEPROM.length()) {
		value = address = 0;
		break;
	  }
	  
	  /***
		As the EEPROM sizes are powers of two, wrapping (preventing overflow) of an
		EEPROM address is also doable by a bitwise and of the length - 1.

		++addr &= EEPROM.length() - 1;
	  ***/	
	}
}
#endif

void setup()
{

  /* Initialize Serial bus */
  Serial.begin( SERIAL_BAUDRATE );

  /* Print EEPROM Size (in bytes) */
  Serial.print("Internal EEPROM size = ");
  Serial.print(EEPROM.length());
  Serial.println(" bytes.");

  
/* Read Initial EEPROM Contents */
#if READ_ENABLE
  ReadInternalEEPROM();
#endif

/* Write New EEPROM Contents */
#if WRITE_ENABLE
  WriteInternalEEPROM();
#endif

/* Read New EEPROM Contents */
#if READ_ENABLE
	ReadInternalEEPROM();
#endif
}

void loop () 
{
	delay(1000);
}
