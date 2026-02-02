#include <Arduino.h>
#include <Wire.h> // I2C Library

#include "LCD_DRIVER.h"

#define lcd_adress 0x27 // I2C address of the LCD

LCD_DRIVER lcd(lcd_adress);

/*PCF8574   → LCD
----------------
P0        → RS
P1        → RW (çoğu kartta GND’ye sabitlenmiş olabilir)
P2        → E
P3        → Backlight
P4        → D4
P5        → D5
P6        → D6
P7        → D7
*/


void setup() {
  
  Serial.begin(115200);
  while (!Serial); // wait for Serial to be ready
  Serial.println("\nStarting I2C LCD");
  Wire.begin();
  
  lcd.init();
  lcd.clear();
  lcd.set_cursor(0, 0); // row 0, column 0
  lcd.print_string("Merhaba!");
}
void loop() {
  // Nothing here
}