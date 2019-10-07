#include <PCD8544.h>

/* PIN definition on Arduino board */
#define SCLK_PIN  3   // Clock pin
#define DIN_PIN   4   // Data In pin
#define DC_PIN    5   // Data/Command select pin 
#define RST_PIN   6   // LCD reset pin
#define SCE_PIN   7   // Select Chip Enable pin

/* Create an object with LCD pins as defined above */
PCD8544 lcd(SCLK_PIN, DIN_PIN, DC_PIN, RST_PIN, SCE_PIN);

#define LCD_WIDTH     84
#define LCD_HEIGHT    48

void setup() {
   lcd.begin(LCD_WIDTH, LCD_HEIGHT);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME  ");
  
  lcd.setCursor(0, 1);
  lcd.print("     To");
  
  lcd.setCursor(0, 2);
  lcd.print("   Softwares");
  
  lcd.setCursor(0, 3);
  lcd.print("   Unleashed");

  lcd.setCursor(0, 5);
  lcd.print("Auth:Sudhanshu");

  delay(200);
}
