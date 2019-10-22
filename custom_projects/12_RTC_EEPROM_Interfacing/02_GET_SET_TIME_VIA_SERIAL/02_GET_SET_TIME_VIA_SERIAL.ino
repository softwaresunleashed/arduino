
#include <Wire.h>

#define SERIAL_BAUDRATE  115200

/* RTC Module I2C address */
#define DS1307_ADDRESS 0x68
byte zero = 0x00;


/* Structure of RTC */
typedef struct DateTime_
{
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t weekday;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
}DateTime_t;

DateTime_t xDateTime;


byte decToBcd(byte val){
// Convert normal decimal numbers to binary coded decimal
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)  {
// Convert binary coded decimal to normal decimal numbers
  return ( (val/16*10) + (val%16) );
}

char * pcGetWeekDayStr( uint8_t uiWeekDay )
{
	char * pcWeekDay = (char *) "INVALID";

	switch( uiWeekDay )
	{
		case 1:
			pcWeekDay = (char *) "Sunday";
		case 2:
			pcWeekDay = (char *) "Monday";
		case 3:
			pcWeekDay = (char *) "Tuesday";
		case 4:
			pcWeekDay = (char *) "Wednessday";
		case 5:
			pcWeekDay = (char *) "Thursday";
		case 6:
			pcWeekDay = (char *) "Friday";
		case 7:
			pcWeekDay = (char *) "Saturday";
	}
	return pcWeekDay;
}

void vGetRtcFromUser()
{
	/* Get Year */
	Serial.print("Enter Year (0 - 99) : ");
	while( Serial.available() == 0 ); // Wait for user input
	xDateTime.year = strtoul(Serial.readString().c_str(), NULL, 0);
	Serial.println(xDateTime.year);

	/* Get Month */
	Serial.print("Enter Month (1 - 12) : ");
	while( Serial.available() == 0 ); // Wait for user input
	xDateTime.month = strtoul(Serial.readString().c_str(), NULL, 0);
	Serial.println(xDateTime.month); 

	/* Get Day */
	Serial.print("Enter Day (1 - 31) : ");
	while( Serial.available() == 0 ); // Wait for user input
	xDateTime.day = strtoul(Serial.readString().c_str(), NULL, 0);
	Serial.println(xDateTime.day); 

	/* Get Week Day */
	Serial.print("Enter Week Day (0 [Sunday] - 6 [Saturday]) : ");
	while( Serial.available() == 0 ); // Wait for user input
	xDateTime.day = strtoul(Serial.readString().c_str(), NULL, 0);
	Serial.println(xDateTime.day);

	/* Get Hour */
	Serial.print("Enter Hour : ");
	while( Serial.available() == 0 ); // Wait for user input
	xDateTime.hour = strtoul(Serial.readString().c_str(), NULL, 0);
	Serial.println(xDateTime.hour); 

	/* Get Minute */
	Serial.print("Enter Minute : ");
	while( Serial.available() == 0 ); // Wait for user input
	xDateTime.minute = strtoul(Serial.readString().c_str(), NULL, 0);
	Serial.println(xDateTime.minute); 

	/* Get Second */
	Serial.print("Enter Second : ");
	while( Serial.available() == 0 ); // Wait for user input
	xDateTime.second = strtoul(Serial.readString().c_str(), NULL, 0);
	Serial.println(xDateTime.second); 

}

void setDateTime()
{
	vGetRtcFromUser();

	byte second =      xDateTime.second;	//0-59
	byte minute =      xDateTime.minute;	//0-59
	byte hour =        xDateTime.hour;		//0-23
	byte weekDay =     xDateTime.weekday;	//1-7
	byte monthDay =    xDateTime.day;		//1-31
	byte month =       xDateTime.month;		//1-12
	byte year  =       xDateTime.year;		//0-99

	Wire.beginTransmission(DS1307_ADDRESS);
	Wire.write(zero); //stop Oscillator

	Wire.write(decToBcd(second));
	Wire.write(decToBcd(minute));
	Wire.write(decToBcd(hour));
	Wire.write(decToBcd(weekDay));
	Wire.write(decToBcd(monthDay));
	Wire.write(decToBcd(month));
	Wire.write(decToBcd(year));

	Wire.write(zero); //start

	Wire.endTransmission();
}

void printDate()
{
	// Reset the register pointer
	Wire.beginTransmission(DS1307_ADDRESS);
	Wire.write(zero);
	Wire.endTransmission();

	Wire.requestFrom(DS1307_ADDRESS, 7);

	int second = bcdToDec(Wire.read());
	int minute = bcdToDec(Wire.read());
	int hour = bcdToDec(Wire.read() & 0b111111); //24 hour time
	int weekDay = bcdToDec(Wire.read()); //0-6 -> sunday - Saturday
	int monthDay = bcdToDec(Wire.read());
	int month = bcdToDec(Wire.read());
	int year = bcdToDec(Wire.read());

	//print the date e.g [Tuesday] 22/10/2019 23:59:59
	Serial.print("- ");
	Serial.print(pcGetWeekDayStr(weekDay));
	Serial.print(" - ");
	Serial.print(monthDay);
	Serial.print("/");
	Serial.print(month);
	Serial.print("/");
	Serial.print(2000 + year);
	Serial.print(" ");
	Serial.print(hour);
	Serial.print(":");
	Serial.print(minute);
	Serial.print(":");
	Serial.println(second);
}

void setup () 
{	
	Wire.begin();
	Serial.begin( SERIAL_BAUDRATE );

	Serial.print("Would you like to setup Date & Time ? ( y or n) : ");
	while( Serial.available() == 0 ); // Wait for user input

	if( strcmp( Serial.readString().c_str(), "y" ) )
	{
		setDateTime(); //MUST CONFIGURE IN FUNCTION
	}	
}

void loop () 
{
	/* Get current time (read from EEPROM) */
	printDate();

	delay(5000);
}
