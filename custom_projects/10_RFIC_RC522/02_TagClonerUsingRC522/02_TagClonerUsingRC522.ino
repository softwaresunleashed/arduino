/*
 * Copy the RFID card data into variables and then 
 * scan the second empty card to copy all the data
 * ----------------------------------------------------------------------------
 * Example sketch/program which will try the most used default keys listed in 
 * https://code.google.com/p/mfcuk/wiki/MifareClassicDefaultKeys to dump the
 * block 0 of a MIFARE RFID card using a RFID-RC522 reader.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 */

#include <SPI.h>
#include <MFRC522.h>


#define OLED_SUPPORTED  0
#if OLED_SUPPORTED
//#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

byte oled_init_success = 0;

void drawWelcomeBanner()
{
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Universal"));

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.setCursor(0,1);
  display.println(F("Cloner"));

  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);

  display.display();
  delay(2000);
}
#endif /* OLED_SUPPORTED */


#define BAUD_RATE   115200
#define DEBUG_ENABLE  1   // 0 to disable debug messages



#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

byte buffer[18];
byte block;
byte waarde[64][16];
MFRC522::StatusCode status;
    
MFRC522::MIFARE_Key key;

// Number of known default keys (hard-coded)
// NOTE: Synchronize the NR_KNOWN_KEYS define with the defaultKeys[] array
#define NR_KNOWN_KEYS   8
// Known keys, see: https://code.google.com/p/mfcuk/wiki/MifareClassicDefaultKeys
byte knownKeys[NR_KNOWN_KEYS][MFRC522::MF_KEY_SIZE] =  {
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // FF FF FF FF FF FF = factory default
    {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5}, // A0 A1 A2 A3 A4 A5
    {0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5}, // B0 B1 B2 B3 B4 B5
    {0x4d, 0x3a, 0x99, 0xc3, 0x51, 0xdd}, // 4D 3A 99 C3 51 DD
    {0x1a, 0x98, 0x2c, 0x7e, 0x45, 0x9a}, // 1A 98 2C 7E 45 9A
    {0xd3, 0xf7, 0xd3, 0xf7, 0xd3, 0xf7}, // D3 F7 D3 F7 D3 F7
    {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff}, // AA BB CC DD EE FF
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 00 00 00 00 00 00
};

char choice;
/*
 * Initialize.
 */
void setup() {  
    Serial.begin(BAUD_RATE);         // Initialize serial communications with the PC
    while (!Serial);            // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

#if OLED_SUPPORTED
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
      Serial.println(F("SSD1306 allocation failed"));
    }
    oled_init_success = 1;  // oled initialized successfully
    if(oled_init_success)
    {
      // Clear the buffer
      display.clearDisplay();
      drawWelcomeBanner();
    }
#endif

    SPI.begin();                // Init SPI bus
    mfrc522.PCD_Init();         // Init MFRC522 card
    delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
    mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
}

//Dump array via serial port in Hexadecimal
void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}

//Dump array via serial port in ASCII
void dump_byte_array1(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.write(buffer[i]);
  }
}


void keuze2()
{ //Test waardes in blokken
  
  for(block = 4; block <= 62; block++)
  {
    if(block == 7 || block == 11 || 
      block == 15 || block == 19 || 
      block == 23 || block == 27 || 
      block == 31 || block == 35 || 
      block == 39 || block == 43 || 
      block == 47 || block == 51 || 
      block == 55 || block == 59)
    {
      block ++;
    }
  
    Serial.print(F("Writing data into block ")); 
    Serial.print(block);
    Serial.println("\n");

    for(int j = 0; j < 16; j++)
    {
      Serial.print(waarde[block][j]);
      Serial.print(" ");
    }

    Serial.println("\n");
  }
}

void keuze3()
{ 
  //Copy the data in the new card
  Serial.println("Insert new card...");
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
    return;

    // Show some details of the PICC (that is: the tag/card)
    Serial.print(F("Card UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();
    Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.println(mfrc522.PICC_GetTypeName(piccType));
    
    // Try the known default keys
    /*MFRC522::MIFARE_Key key;
    for (byte k = 0; k < NR_KNOWN_KEYS; k++) {
        // Copy the known key into the MIFARE_Key structure
        for (byte i = 0; i < MFRC522::MF_KEY_SIZE; i++) {
            key.keyByte[i] = knownKeys[k][i];
        }
    }*/

  for (byte i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }

  for(int i = 4; i <= 62; i++)
  { 
      //De blocken 4 tot 62 kopieren, behalve al deze onderstaande blocken (omdat deze de authenticatie blokken zijn)
      if(i == 7 || i == 11 || i == 15 || i == 19 || 
      i == 23 || i == 27 || i == 31 || i == 35 || 
      i == 39 || i == 43 || i == 47 || i == 51 || 
      i == 55 || i == 59)
      {
        i++;
      }

      block = i;
      
    // Authenticate using key A
    Serial.println(F("Authenticating using key A..."));
    status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK)
    {
      Serial.print(F("PCD_Authenticate() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }

    // Authenticate using key B
    Serial.println(F("Authenticating again using key B..."));
    status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, block, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

  // Write data to the block
  Serial.print(F("Writing data into block ")); 
  Serial.print(block);
  Serial.println("\n");
          
  dump_byte_array(waarde[block], 16); 
          
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Write(block, waarde[block], 16);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
  }

  Serial.println("\n"); 
  }
  mfrc522.PICC_HaltA();       // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
}

void readCard(){ 
  //Read card
  Serial.print("Swipe RFID card...Waiting");

  // Wait for new card along with timeout
  int timeout = 5;    // Try x number of times
  while(1)
  {
    if ( !mfrc522.PICC_IsNewCardPresent() )
    {
      if(timeout == 0)
      {
        Serial.println("Timed Out.");
        return;  
      }

      Serial.print(".");
      timeout--;
      
      delay(2000);    //wait for 2 seconds
    }
    else
    {
       break;  
    }
  };

  // Reset Timed Out to x number of retries
  timeout = 5;
  while(1)
  {
    if ( !mfrc522.PICC_ReadCardSerial() )
    {
      if(timeout == 0)
      {
        Serial.println("Read Card Timed Out.");
        return;  
      }

      Serial.print(".");
      timeout--;  

      delay(2000);    //wait for 2 seconds
    }
    else
    {
      break;  
    }
  };

#if 0
    // Dump debug info about the card; PICC_HaltA() is automatically called
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
#endif

  // Show some details of the PICC (that is: the tag/card)
  Serial.println(F("Card UID:"));
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();
  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));

  // Try the known default keys
  MFRC522::MIFARE_Key key;
  for (byte k = 0; k < NR_KNOWN_KEYS; k++) 
  {
    // Copy the known key into the MIFARE_Key structure
    for (byte i = 0; i < MFRC522::MF_KEY_SIZE; i++)
    {
      key.keyByte[i] = knownKeys[k][i];
    }

    // Try the key
    if (try_key(&key)) {
      // Found and reported on the key and block,
      // no need to try other keys for this PICC
      break;
    }
  }
}

void start()
{
  while( Serial.available() == 0 ); // Wait for user input
  String choice = Serial.readString();    // cliOption = "y + NULL" or "n + NULL"
  if( strncmp( choice.c_str(),"1", 1) == 0 ) // Option 1 selected
  {
    Serial.println("Read the card");
    readCard();
  }
  else if ( strncmp( choice.c_str(),"2", 1) == 0 )  // Option 2 selected
  {
    Serial.println("See what is in the variables");
    keuze2();
  }
  else if ( strncmp( choice.c_str(),"3", 1) == 0 )  // Option 3 selected
  {
    Serial.println("Copying the data on to the new card");
    keuze3();
  }
}


/*
 * Try using the PICC (the tag/card) with the given key to access block 0 to 63.
 * On success, it will show the key details, and dump the block data on Serial.
 *
 * @return true when the given key worked, false otherwise.
 */
 
bool try_key(MFRC522::MIFARE_Key *key)
{
    bool result = false;
    
    for(byte block = 0; block < 64; block++)
  {

#if DEBUG_ENABLE
    Serial.print(F("Authenticating using key A..."));
    dump_byte_array( key->keyByte, MFRC522::MF_KEY_SIZE);
    Serial.println();
#endif
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return false;
    }

    // Read block
    byte byteCount = sizeof(buffer);
    status = mfrc522.MIFARE_Read(block, buffer, &byteCount);
    if (status != MFRC522::STATUS_OK)
    {
      Serial.print(F("MIFARE_Read() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
    }
    else
    {
      // Successful read
      result = true;
      Serial.print(F("Success with key:"));
      dump_byte_array((*key).keyByte, MFRC522::MF_KEY_SIZE);
      Serial.println();

      // Dump block data
      Serial.print(F("Block ")); Serial.print(block); Serial.print(F(":"));
      dump_byte_array1(buffer, 16); //omzetten van hex naar ASCI
      Serial.println();

      for (int p = 0; p < 16; p++) //De 16 bits uit de block uitlezen
      {
        waarde [block][p] = buffer[p];
        Serial.print(waarde[block][p]);
        Serial.print(" ");
      }        
    }
  }

  Serial.println();
  mfrc522.PICC_HaltA();       // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  return result;
}

/*
 * Main loop.
 */
void loop() {  
  Serial.println("\n\nWhat would you like to do ? \n1.Read card \n2.Write to card \n3.Copy the data.");
  start();  
}
