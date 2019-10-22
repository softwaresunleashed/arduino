/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 * 
 * Change this define to match your SD shield or module;
 * Arduino Ethernet shield: pin 4
 * Adafruit SD shields and modules: pin 10
 * Sparkfun SD shield: pin 8
 * MKRZero SD: SDCARD_SS_PIN
const int chipSelect = 10;
 *  For Adafruit kind MMC Shield
 ** CS - pin 4
 */
#include <SPI.h>
#include <SD.h>

/* Defines */

/* Change 'CS' define to match your SD shield or module;
 * Arduino Ethernet shield: pin 4
 * Adafruit SD shields and modules: pin 10
 * Sparkfun SD shield: pin 8
 * MKRZero SD: SDCARD_SS_PIN
 */
#define CS_PIN  10  /* Chip Select / Slave Select */
#define SERIAL_BAUDRATE  115200

/* Global structures */
File myFile;
Sd2Card card;
SdVolume volume;
SdFile root;

#define PRINT_MMC_INFO  0
#if PRINT_MMC_INFO
void vPrintMMCInfo( Sd2Card card )
{
    Serial.print("\nInitializing SD card...");

    // we'll use the initialization code from the utility libraries
    // since we're just testing if the card is working!
    if ( !card.init( SPI_HALF_SPEED, CS_PIN ) ) {
      Serial.println("Initialization failed. \nThings to check:");
      Serial.println("* is a card inserted?");
      Serial.println("* is your wiring correct?");
      Serial.println("* did you change the chipSelect pin to match your shield or module?");
      while (1);
    } else {
      Serial.println("Wiring is correct and a card is present.");
    }

  // print the type of card
  Serial.println();
  Serial.print("Card type:         ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    while (1);
  }

  Serial.print("Clusters:          ");
  Serial.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:  ");
  Serial.println(volume.blocksPerCluster());

  Serial.print("Total Blocks:      ");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  Serial.print("Volume size (Kb):  ");
  Serial.println(volumesize);
  Serial.print("Volume size (Mb):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Gb):  ");
  Serial.println((float)volumesize / 1024.0);

  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);    
} 
#endif /* PRINT_MMC_INFO */

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin( SERIAL_BAUDRATE );
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

#if PRINT_MMC_INFO
  vPrintMMCInfo( card );
#else

  // For Mega boards with an Ethernet shield, make sure the Wiznet
  // chip is not selected:
  pinMode( CS_PIN, OUTPUT );
  digitalWrite( CS_PIN, HIGH );

#if 1
  Serial.print("Initializing SD card...");

  if ( !card.init(SPI_HALF_SPEED, CS_PIN ) ) {
    Serial.println("Initialization failed. \nThings to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    while (1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }

  // Now we will try to open 
  // the 'volume'/'partition' - it should be FAT16 or FAT32
  Serial.print("Initializing Volume / Partition");
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    while (1);
  }
  Serial.println("...Done.");
#else if 

  if (!SD.begin( CS_PIN, SPI_HALF_SPEED )) {
    Serial.println("Initialization failed!");
    while (1);
  }
#endif 

  if( root.openRoot(volume) )
  {
     Serial.println("Open Root Success!");
     while(1);
  }
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

 
#endif
}

void loop() {
  // nothing happens after setup
}
