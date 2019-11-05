/*
  IR Receiver Demonstration 3
  IR-Rcv-Demo3.ino
  Control LED's using Unused IR Remote keys

  DroneBot Workshop 2017
  http://dronebotworkshop.com
*/

// Include IR Remote Library by Ken Shirriff
#include <IRremote.h>

// Define sensor pin
const int RECV_PIN = 4;

// Key Hex codes go here...
// SONY TV Remote
#define RED_KEY_HEX_CODE      0x52E9
#define YELLOW_KEY_HEX_CODE   0x72E9
#define VOL_UP                0x490
#define VOL_DOWN              0xC90
#define CHANNEL_UP            0X090
#define CHANNEL_DOWN          0x890


// Define LED pin constants
const int redPin = 8; 
const int yellowPin = 7;

// Define integer to remember toggle state
int togglestate = 0;

// Define IR Receiver and Results Objects
IRrecv irrecv(RECV_PIN);
decode_results results;

#define BAUD_RATE   115200

void setup(){
  // Initialize Serial Monitor
  Serial.begin( BAUD_RATE );

  Serial.println(" Ready to recieve IR signal from IR sources ...");
  
  // Enable the IR Receiver
  irrecv.enableIRIn();
  
  // Set LED pins as Outputs
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
}

void loop(){
    if (irrecv.decode(&results)){

        switch(results.value){
          case RED_KEY_HEX_CODE: //Red Keypad Button
            // Turn on LED for 2 Seconds
            Serial.print("LED On...");
            digitalWrite(redPin, HIGH);
            delay(2000);
            digitalWrite(redPin, LOW);
            Serial.println("LED Off.");
            break;
   
          case YELLOW_KEY_HEX_CODE: //Yellow Keypad Button
            // Toggle LED On or Off
            togglestate = togglestate ^ 1;
            if(togglestate)
            {
              Serial.println("LED Toggle On.");
            }
            else
            {
              Serial.println("LED Toggle Off.");
            }  
            digitalWrite(yellowPin, togglestate);
            break;     
    }
    irrecv.resume(); 
  }
}
