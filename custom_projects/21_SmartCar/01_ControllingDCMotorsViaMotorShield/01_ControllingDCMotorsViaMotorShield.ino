#include <AFMotor.h>


#define BAUDRATE    115200
#define DELAY       5000

// Create Motor(s) objects
/*
Valid Values :
------------
Motor 1 & 2 : MOTOR12_64KHZ | MOTOR12_8KHZ  | MOTOR12_2KHZ  | MOTOR12_1KHZ
Motor 3 & 4 : MOTOR34_64KHZ | MOTOR34_8KHZ  |  ----------   | MOTOR34_1KHZ
*/
AF_DCMotor motor1(1, MOTOR12_1KHZ); // create motor #1, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_1KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor3(3, MOTOR34_1KHZ); // create motor #3, 64KHz pwm
AF_DCMotor motor4(4, MOTOR34_1KHZ); // create motor #4, 64KHz pwm

// Set Speed of Individual Motors
void setMotorSpeeds()
{
  #define INITIAL_SPEED     200
  // Valid speeds are between 0 to 255
  motor1.setSpeed( INITIAL_SPEED );     // set the speed to 200/255
  motor2.setSpeed( INITIAL_SPEED );     // set the speed to 200/255
  motor3.setSpeed( INITIAL_SPEED );     // set the speed to 200/255
  motor4.setSpeed( INITIAL_SPEED );     // set the speed to 200/255
}

void setup() {
  Serial.begin(BAUDRATE);           // set up Serial library at BAUDRATE bps
  Serial.println("Motor test!");

  setMotorSpeeds();
}
 
void loop() {
  Serial.println("tick");

  // Go Forward
  motor1.run( FORWARD );
  motor2.run( FORWARD );
  motor3.run( FORWARD );
  motor4.run( FORWARD );
  delay( DELAY );

  // Go Backward
  Serial.println("tock");
  motor1.run( BACKWARD );
  motor2.run( BACKWARD );
  motor3.run( BACKWARD );
  motor4.run( BACKWARD );
  delay( DELAY );

  // Stop motors
  Serial.println("tack");
  motor1.run( RELEASE );
  motor2.run( RELEASE );
  motor3.run( RELEASE );
  motor4.run( RELEASE );
  delay( DELAY );
}
