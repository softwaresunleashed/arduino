// FC-04 Sound Sensor Demo by Bradley S. Worthington-White 12/11/2015

/*
 *  Housekeeping notice:  Any line, sentence, phrase, whatever... that begins with "//" is a comment.  Comments are ignored by the program but shouldn't be by you.
 *  Commenting your files will help you, and others, figure out what you were doing and why you did it when you come back and look at a sketch a year later.  
 *  Oh yeah, this note your reading is commented using another technique for adding comments.  The "/*" denotes the beginning of the comment and the "* /" (without the space) 
 *  denotes the end of the comment.  This commenting technique is normally reserved for longer comments, such as this!
*/

/*  Setup instructions for use with this sketch.
 *   1.  5v from Arduino to Vcc in on sound module
 *   2.  GND from Arduino to GND on sound module
 *   3.  OUT from sound module to A4 (analog pin #4 on Arduino)
 *   4.  add two (2) 150ohm resistors to breadboard and run 5v out from Arduino to one leg of each
 *   5.  connect the positive leg of an LED to the opposite end of one of the resistors (not the end you just put the 5v on)
 *   6.  do the same for the other LED and other resistor
 *   7.  connect the negitive leg of the LEDs to the Arduino GND
 *   8.  IMPORTANT: (also see "IMPORTANT..." below for more info on this) The FC-04 has two on-board LEDs; Red, power on / Green, on when sound is detected - adjust the 
 *       on-board potentiometer (POT) until the Green LED comes on and then back it off, every so slightly, just to the point where that Green LED wants to come on 
 *       but won't without sound being present 
 */
 
 /* IMPORTANT, IMPORTANT, IMPORTANT,  READ THIS:  
 *  
 *  1.  The FC-04 sound sensors have a potentiometer (POT) on them and all the information regarding that POT says it is for adjusting sensitivity.  IT DOES NOT
 *  adjust the sensitivity of the microphone pickup, it does adjust the voltage (internally) at which sound triggers the output.  Fine tuning this POT was crucial for this sketch to
 *  function correctly. You want it adjusted so it's just below the level that sound starts to trigger it.
 * 
 */

// We begin each sketch by setting up some things that will be used thoughout your sketch.

const int SenOut = A4; // "SenOut" (my word for the sensor's OUT pin) is created and assigned to digital pin #4
const int LED1 = 2; // "LED1" is created and assigned to digital pin #2
const int LED2 = 4; // "LED2" is created and assigned to digital pin #4

/*  The above "const int" statements create constant itergers - got that?  A "constant" is something the will not (and can not)
 *  change within your script, it is "constant".  And interger is just the data type, probably the most common type you'll use.  An interger is a whole number; 1,15,35, 
 *  and -46 are examples of intergers whereas 7.25 or 6 1/2 are not.  The const int's above can all now be referred to directly by name (IE: SenOut) in your sketch.
 *  You don't have to remember the "LED1" is on digital pin 2, you just have to remember "LED1".  In addition, if you were to move "LED1" from pin 2 to
 *  pin 5 you don't have to hunt through your sketch looking for every reference to "LED1" and change it to pin 5.  Change the #2 to #5 after LED1 above and
 *  you're done.  Every reference in your sketch with "LED1" in it will now reference pin 5, not pin 2.
  */

int sensorValue = 0; // The word "sensorValue" is created and assigned an initial value of zero (0)

/*  Pretty much the same as above, but note the lack of "const" in front of "int".  Here we are creating a varialbe that can, and most likely will, change it's value.
 *  Variables can be thought of as storage locations for data you want to recall later and/or manipulate in some manner.
*/

void setup()    // the "void setup()" section below is used to configure your board for your project and intitialize some items as well.  
{
  pinMode(LED1, OUTPUT);  // configuring digital pin #2 as output (But it doesn't say anything about pin #2?  True, but remember the const int we set above.)   
  pinMode(LED2, OUTPUT); // configuring digital pin #4 as output
  pinMode(SenOut, INPUT); // configuring analog pin #A4 as input
  
  Serial.begin(9600);  // initializing the Arduino USB to Serial interface (so we can see stuff on the serial monitor - more on that later) 
}

/*  Everything above this point in a skectch is only read ONCE when a sketch starts.  After which the "void loop()" section below is read and repeated over and over    
 *  until you pull the plug or something breaks.
 */
 
void loop()   // the "void loop()" section is where your main code is contained.
{

sensorValue = analogRead(SenOut); // the value to be stored in "sensorValue" will be obtained by reading the current value of analog pin #4  


if (sensorValue > 850) // "if" statements are pretty much your bread and butter when coding.  Here we're saying "if" the value in "sensorValue" is greater than 850 then...
  {
    digitalWrite(LED1, HIGH); // then... do this, set digital pin #2 HIGH - turning on LED1 
    digitalWrite(LED2, LOW);  // then... also do this, set digital pin #4 LOW - turning off LED2
  }

/* "if" above will only excute the commands in the "if statement" (the code between the { and } brackets below "if") if the condition(s) is TRUE.  In this case, the if 
 *  condition is TRUE only if the value stored sensorValue is greater than 850.  If the condition is FALSE the commands in the "if statement" will be ignored.  
 *  And that's where "else" and "else if" come into play.  We're saying IF this is TRUE then do these things. IF it is FALSE then look for "else" or "else if" and see 
 *  if they're TRUE   
 */
  
else if (sensorValue < 950)
  
  /* So if sensorValue wasn't greater than 850, the "else if" line above is the next line of code the program will pay attention to.  The commands in the "if statement(s)" 
   * for 'else if' will be executed "if" the sensorValue is less than 950 and if so then... 
   */
   {
    digitalWrite(LED2, HIGH); // then... do this, set digital pin #4 HIGH, turning on LED2
    digitalWrite(LED1, LOW);   // then... also do this, set digital #2 LOW, turning off LED1
    delay(50); // DO NOT remove this delay, required for functionality
   }
/*  Debugging
 *   
 * Uncommenting the items below will send the "senorValue" data to the serial monitor, you can then use the potetionmeter on the sensor to adjust the sensor for optimal response
 * with this sketch.  The "at rest" (no sound detected) value should be 1022 or 1023.  Adjust the sensor (via the POT) so that the value monitored value drops as soon as 
 * sound is detected   
 * 
 * DO NOT FORGET TO COMMENT OUT THE DEBUGGING LINES BELOW WHEN YOU ARE DONE  
 */
 
// Serial.println(sensorValue); // sends the value we just stored in "senorValue" to the screen (serial monitor).
// Serial.println(); // adds blank line on monitor for readability
// delay(500); // this delay is for readabilty of info on screen, increasing the number will slow things down for you

/*  Debugging END
 *   DO NOT FOGET TO COMMENT THIS SECTION OUT AFTER DEBUGGING
 *   The delay introduced here for debugging will interfere with the normal functionality of this sketch 
 */


} // The End  Good, I can stop typing now!

/* Oops, I almost forgot the serial monitor, if you haven't used it before now is your chance.  It is a great tool for displaying responses from your sketch on screen; to showoff
 *  or even better for debugging.
 *  To start the serial monitor, in the Arduino interface, look up in the top right corner.  There's an icon there (looks like a magnifying glass to me), click it and the serial monitor
 *  will start.  You can also start the serial monitor via TOOLS / Serial Monitor or CTRL+SHIFT+M.
 *  
 *  OK, now I'm done!  Thank you and good night.
 */
