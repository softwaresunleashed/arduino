/*
  IR Transmitter Demonstration 1
  IR-Xmit-Demo1.ino
  Control TV using IR Library
  IR LED must use Pin #3
  DroneBot Workshop 2017
  http://dronebotworkshop.com
*/

// Include IR Remote Library by Ken Shirriff

#include <IRremote.h>

// Key Hex codes go here...
// SONY TV Remote
#define VOL_UP                0x490
#define VOL_DOWN              0xC90

// Define switch pin
#define SWITCH_PIN    7

// Delay in msecs between individual remote key signals
#define DELAY_BW_KEYS  20

// Define a variable for the button state
int buttonState = 0;

// Create IR Send Object
IRsend irsend;

#define SONY_IR_BITS  12
#define BAUD_RATE     115200

void setup()
{
  // Initialize Serial Monitor
  Serial.begin( BAUD_RATE );

  // Set Switch pin as Input
  pinMode(SWITCH_PIN, INPUT);
}

void volumeUp()
{
  Serial.println("Vol Up...");
  irsend.sendSony(VOL_UP, SONY_IR_BITS); // TV Vol Key IR code
  delay( DELAY_BW_KEYS );
}

void volumeDown()
{
  Serial.println("Vol Down...");
  irsend.sendSony(VOL_DOWN, SONY_IR_BITS); // TV Vol Key IR code
  delay( DELAY_BW_KEYS );
}

void loop() {
  // Set button state depending upon switch position
  buttonState = digitalRead( SWITCH_PIN );

  // If button is pressed send power code command
  if (buttonState == HIGH)
  {
      // Enable Volume Up or Disable as required
      volumeUp();
      //volumeDown();
  }
  
  // Add a small delay before repeating
  //delay( DELAY_BW_KEYS );
} 
