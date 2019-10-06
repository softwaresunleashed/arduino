// Code for testing Temperature Sensor over Serial Port

#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is plugged into pin 5 on Ardiuno
#define ONE_WIRE_BUS 5
 
// Setup a oneWire instance to communicate with any OneWire 
// devices (not just lcMaxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
 
void setup(void)
{
  // start serial port
  Serial.begin(115200);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
}
 
 
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print(" Requesting temperatures...");

  // Send the command to get temperatures
  sensors.requestTemperatures(); 
  Serial.println("DONE");

  Serial.print("Temperature for Device 1 is: ");
  Serial.print(sensors.getTempCByIndex(0)); 
    // You can have more than one IC on the same bus. 
    // 0 refers to the first IC on the wire

  delay(20000);
}
