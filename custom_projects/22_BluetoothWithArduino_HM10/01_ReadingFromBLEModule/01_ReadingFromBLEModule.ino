/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digitx
 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example
 modified 13 Oct 2019
 by Sudhanshu Gupta

 This example code is in the public domain.

 */


#include <SoftwareSerial.h>

//SoftwareSerial BtSerial(15, 14); // RX, TX
//SoftwareSerial BtSerial(19, 18); // RX, TX
SoftwareSerial BtSerial(10, 11); // RX, TX

#define BAUDRATE    115200

char c=' ';
boolean NL = true;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(BAUDRATE);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }

  Serial.println("\n\r ");
  Serial.print("Sketch: "); Serial.println(__FILE__);
  Serial.print("Uploaded: "); Serial.println(__DATE__);
  Serial.println(" ");
  
  // set the data rate for the SoftwareSerial port
  BtSerial.begin(BAUDRATE);
  BtSerial.print("Software Serial Port started at "); 
  BtSerial.println(BAUDRATE);
}

void loop() // run over and over
{
  if (BtSerial.available())
  {
    c = BtSerial.read();
    Serial.write(c);
  }
  
  // Read from the Serial Monitor and send to the Bluetooth module  
  if (Serial.available())
  {
    // Read one char at a time from UART
    c = Serial.read();
    // Write one char at a time to BT port (via Software Serial Pins - PWM)
    BtSerial.write(c);

    // Echo whatever we type on Serial Port
    Serial.write(c);
  }
  
}
