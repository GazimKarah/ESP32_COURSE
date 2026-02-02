#include <Arduino.h>
#include <Wire.h> // I2C Library

#define lcd_adress 0x27 // I2C address of the LCD

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
  Serial.println("\nStarting Backlight I2C LCD test...");
  Wire.begin(); // Start I2C as Master (SDA : GPIO21, SCL : GPIO22)

  delay(1000); // wait for LCD to power up
  Wire.beginTransmission(lcd_adress);
  Wire.write(0x30); 
  Wire.write(0x34);
  Wire.write(0x30);
  Wire.endTransmission();
  delay(5);

  Wire.beginTransmission(lcd_adress);
  Wire.write(0x20);
  Wire.write(0x24);
  Wire.write(0x20);
  Wire.endTransmission();
  delayMicroseconds(50);
  
  Wire.beginTransmission(lcd_adress);
  Wire.write(0x20);
  Wire.write(0x24);
  Wire.write(0x20);
  Wire.endTransmission();
  delayMicroseconds(50);

  Wire.beginTransmission(lcd_adress);
  Wire.write(0x00);
  Wire.write(0x04);
  Wire.write(0x00);

  Wire.write(0x0C); 
  Wire.write(0x0C4);
  Wire.write(0x0C);
  Wire.endTransmission();
  delayMicroseconds(50);

  Wire.beginTransmission(lcd_adress);
  Wire.write(0x00);
  Wire.write(0x04);
  Wire.write(0x00);

  Wire.write(0x18); 
  Wire.write(0x1C);;
  Wire.write(0x18);
  Wire.endTransmission();
  delay(2);

  Wire.beginTransmission(lcd_adress);
  Wire.write(0x08);
  Wire.write(0x0C);
  Wire.write(0x08);

  Wire.write(0x68);
  Wire.write(0x6C);
  Wire.write(0x68);
  Wire.endTransmission();

  delay(5);

// Now the LCD is initialized, we can write some text
Wire.beginTransmission(lcd_adress);
Wire.write(0x80); // Set cursor to first line, first position
Wire.write(0x84);
Wire.write(0x80);

Wire.write(0x08);
Wire.write(0x0C);
Wire.write(0x08);
Wire.endTransmission();

Wire.beginTransmission(lcd_adress);
Wire.write(0x49); 
Wire.write(0x4D);
Wire.write(0x49);

Wire.write(0x19);
Wire.write(0x1D);
Wire.write(0x19);
Wire.endTransmission();
delayMicroseconds(50);

}
void loop() {
  // Nothing here


}