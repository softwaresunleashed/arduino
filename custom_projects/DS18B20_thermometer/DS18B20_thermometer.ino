/*
 *    Example-Code that emulates a DS18B20
 *
 *    Tested with:
 *    - https://github.com/PaulStoffregen/OneWire --> DS18x20-Example, atmega328@16MHz as Slave
 *    - DS9490R-Master, atmega328@16MHz and teensy3.2@96MHz as Slave
 */

#include "OneWireHub.h"
#include "DS18B20.h"  // Digital Thermometer, 12bit

constexpr uint8_t pin_led       { 13 };
constexpr uint8_t pin_onewire   { 5 };

auto hub    = OneWireHub(pin_onewire);

auto ds18b20 = DS18B20(DS18B20::family_code, 0x00, 0x00, 0xB2, 0x18, 0xDA, 0x00); // DS18B20: 9-12bit, -55 -  +85 degC
//auto ds18s20 = DS18B20(0x10, 0x00, 0x00, 0xA2, 0x18, 0xDA, 0x00);                 // DS18S20: 9   bit, -55 -  +85 degC
//auto ds1822  = DS18B20(0x22, 0x00, 0x00, 0x22, 0x18, 0xDA, 0x00);                 // DS1822:  9-12bit, -55 - +125 degC


void setup()
{
    Serial.begin(115200);
    Serial.println("OneWire-Hub DS18B20 Temperature-Sensor");
    Serial.flush();

    pinMode(pin_led, OUTPUT);

    // Setup OneWire
    hub.attach(ds18b20);
//    hub.attach(ds18s20);
//    hub.attach(ds1822);


    Serial.println("config done");
}

void loop()
{
    // following function must be called periodically
    hub.poll();
    // this part is just for debugging (USE_SERIAL_DEBUG in OneWire.h must be enabled for output)
    if (hub.hasError()) hub.printError();

    Serial.println(ds18b20.getTemperature());
}
