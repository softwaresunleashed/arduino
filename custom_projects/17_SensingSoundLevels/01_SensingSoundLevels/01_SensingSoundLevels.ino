
#define BAUDRATE    115200

#define MIC_PIN   0       /* the microphone amplifier output is connected to pin A0 */
#define INDICATOR_PIN 13
#define DIGITAL_OUT_PIN 10

/* General Threshold after which sound is annoying to ears (found using hit n trial at home)  */ 
#define DECIBLE_THRESHOLD   57    

#define DEBUG_ENABLE    1
#define LOOP_DELAY      2000    /* 2 secs */

void reduceVolume()
{
  /* Send IR code to reduce volume */


  
}



void increaseVolume()
{
  /* Send IR code to increase volume */


  
}


int convertToDb( int AdcValue )
{
  int dB = 0;

  //Convert ADC value to dB using Regression values
  dB = ( AdcValue + 83.2073 ) / 11.003;  

  return dB;
}

int calculateSoundLevel()
{
  int adcVal = analogRead( MIC_PIN );
  return convertToDb( adcVal );
}

void setup() {
  Serial.begin( BAUDRATE ); //sets the baud rate on the Serial Monitor
  pinMode( INDICATOR_PIN, OUTPUT );
  pinMode( DIGITAL_OUT_PIN, OUTPUT );
}

void loop()
{
  int dBVal = 0;
  int adcVal = 0;
  int digVal = 0;
  
  adcVal = analogRead( MIC_PIN ); //Read the ADC value from amplifer 

#if DEBUG_ENABLE
  // Print ADC Value
  Serial.print("ADC Value : ");
  Serial.print( adcVal );//Print ADC for initial calculation 
#endif 

  /* Convert ADC value coming out of Sound Sensor */
  dBVal = convertToDb( adcVal );

#if DEBUG_ENABLE
  // Print Digital Value  
  digVal = digitalRead(DIGITAL_OUT_PIN); //Read the ADC value from amplifer 
  Serial.print("\t\t Dig Value : ");
  Serial.print(digVal); //Print dB for initial calculation 

  // Print dB Value
  Serial.print("\t\t dB Value : ");
  Serial.println(dBVal); //Print dB for initial calculation 
#endif

  if ( dBVal > DECIBLE_THRESHOLD )
  {
#if DEBUG_ENABLE
    digitalWrite(INDICATOR_PIN, HIGH);    // turn the LED on (HIGH is the voltage level)
    delay(2000);                          // wait for a second
    digitalWrite(INDICATOR_PIN, LOW);
#endif

    /* We need to reduce volume till it matches DECIBLE_THRESHOLD */
    while( calculateSoundLevel() == DECIBLE_THRESHOLD )
    {
      reduceVolume();
    }
  }
  else if( dBVal < DECIBLE_THRESHOLD )
  {
    /* We need to increase volume till it matches DECIBLE_THRESHOLD */
    while( calculateSoundLevel() == DECIBLE_THRESHOLD )
    {
      increaseVolume();  
    }    
  }

  delay( LOOP_DELAY );
}
