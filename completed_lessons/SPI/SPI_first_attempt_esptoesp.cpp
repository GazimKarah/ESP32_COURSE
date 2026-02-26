#include <Arduino.h>
#include "SPI.h"

#define DEFAULT_SCK_PIN 18
#define DEFAULT_MISO_PIN 19
#define DEFAULT_MOSI_PIN 23
#define CSS_SS 5

byte data = 0b01011001;
SPIClass *vspi = NULL; //Empty object for spi ( like hwtimer thing )


void setup() {

  Serial.begin(115200);

  vspi = new SPIClass(VSPI);

  vspi->begin(DEFAULT_SCK_PIN,DEFAULT_MISO_PIN,DEFAULT_MOSI_PIN,CSS_SS); //for reach the object adress which is holding the first adress of class, and look for function ((*vspi).begin())

  pinMode(CSS_SS,OUTPUT);

  digitalWrite(CSS_SS,HIGH); // To make sure it is not waken
  
  vspi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

  digitalWrite(CSS_SS,LOW); // To start communication 

  byte gelenveri = vspi -> transfer(data);

  digitalWrite(CSS_SS,HIGH); // To the end

  vspi -> endTransaction();

  Serial.printf("Giden: %d | Gelen: %d\n", data, gelenveri);
  delay(1000);

}
void loop() {
 


}
