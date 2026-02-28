#include <Arduino.h>
#include "SPI.h"
#include "ST7789_DRIVER.h"

// ST7789 Connections
// Vcc - 3v3
// GND - GND
// SCL - GPIO 18
// SDA - GPIO 23
// RES - GPIO 17 (Reset Pin)
// DC - GPIO 16 (data/command)
// BLK (Backlight) -  3v3 (temporary)


#define DEFAULT_SCL_PIN 18
#define DEFAULT_MOSI_PIN 23
#define DC 16
#define RES 17



//For init sequence: SWRESET -> SLPOUT -> COLMOD -> DISPON
//Then, this example's algorithm: CASET -> RASET -> RAMWR

SPIClass *vspi = NULL; //Empty object for spi ( like hwtimer thing 
TFT_Driver *screen = NULL;

void setup() {

  pinMode(18, OUTPUT);
  digitalWrite(18, LOW); 
  delay(100);

  vspi = new SPIClass(VSPI);

  vspi->begin(DEFAULT_SCL_PIN,-1,DEFAULT_MOSI_PIN,-1); //for reach the object adress which is holding the first adress of class, and look for function ((*vspi).begin())

  screen = new TFT_Driver(vspi,DC,RES);

  screen -> init();

  screen ->fillScreen(0XF800,32,32,96,96);

}
void loop() {
 


}
