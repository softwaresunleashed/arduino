/*
  IR Receiver Demonstration 4
  IR-Rcv-Demo4.ino
  Demonstrates IR codes with Custom Remote and IR Receiver
  Makes use of Repeat function

  DroneBot Workshop 2017
  http://dronebotworkshop.com
*/

// Include IR Remote Library by Ken Shirriff
#include <IRremote.h>

// Include Arduino Servo Library
#include <Servo.h>

// Remote Key Codes
// Warmex - NEC based - 32Bits
#define KEY_VOL_UP    0xFF31CE
#define KEY_VOL_DOWN  0xFF11EE
#define KEY_ON_OFF    0xFF19E6
#define KEY_MODE      0xFF29D6
#define KEY_TIMER     0xFF09F6

#define DELAY         30
#define KEY_REPEAT_CODE    0xFFFFFFFF

// Define Sensor Pin
const int RECV_PIN = 4;

// Define Servo Pin
const int SERVO_PIN = 6;

// Define Variable for Servo position
// Start at 90 Degrees (Center position)
int pos = 90;         

// Define variable to store last code received
unsigned long lastCode; 

// Define IR Receiver and Results Objects
IRrecv irrecv(RECV_PIN);
decode_results results;

// Create servo object
Servo myservo;          

void setup()
{
  // Start the receiver
  irrecv.enableIRIn();
   
  // Attach the servo
  myservo.attach(SERVO_PIN); 

  // Start with Servo in Center
  myservo.write(pos); 
}

void loop() {
  if( irrecv.decode(&results) ) //this checks to see if a code has been received
  {
      if( results.value == KEY_REPEAT_CODE )   
      {
         // If Repeat then use last code received
         results.value = lastCode;        
      }
  
      if( results.value == KEY_VOL_UP )    
      {
          // Left Button Pressed
          lastCode = results.value;
          // Move left 2 degrees     
          pos += 2; 
          // Prevent position above 180
          if(pos > 180){pos = 180;}                     
          myservo.write(pos);      
      }
        
      if( results.value == KEY_VOL_DOWN )     
      {
         // Right Button Pressed
         lastCode = results.value;
         // Move Right 2 degrees  
         pos -= 2; 
         // Prevent position below 0
         if(pos < 0){pos = 0;}                   
         myservo.write(pos);     
      }
  
     if( results.value == KEY_ON_OFF )     
      {
         // Center Button Pressed
         lastCode = results.value;
         // Move to Center  
         pos = 90;          
         myservo.write(pos);     
      }
  
      // Add delay to prevent false readings
      delay( DELAY );
          
      //receive the next value  
      irrecv.resume(); 
  }    
}
