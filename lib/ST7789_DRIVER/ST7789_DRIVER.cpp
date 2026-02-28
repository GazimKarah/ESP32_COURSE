#include "ST7789_DRIVER.h"


TFT_Driver::TFT_Driver(SPIClass* spi_bus, uint8_t dc_pin, uint8_t rst_pin)
{

    _spi = spi_bus;
    _dc = dc_pin;
    _rst = rst_pin;

    pinMode(_dc, OUTPUT);
    pinMode(_rst,OUTPUT);
}

void TFT_Driver::sendCommand(uint8_t command){

    digitalWrite(_dc,LOW);
    _spi -> transfer(command); 

}
void TFT_Driver::sendData(uint8_t data){

    digitalWrite(_dc,HIGH);
    _spi -> transfer(data); 

}

void TFT_Driver::init(){

    digitalWrite(_rst, HIGH); 
    delay(50); 
    digitalWrite(_rst, LOW);  // Ekranın beynini kapat
    delay(50);                // 50ms bekle (10 yetmez)
    digitalWrite(_rst, HIGH); // Uykudan kaldır
    delay(150);               // İç osilatörlerin toparlanması için 150ms kesin bekle!

    _spi -> beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

    sendCommand(SWRESET);
    delay(150);

    sendCommand(SLPOUT);
    delay(120);

    sendCommand(COLMOD);
    sendData(0x55); //RGB565 (5 bit red, 6 bit green, 5 bit blue)
    delay(5);

    sendCommand(DISPON);
    delay(10);

    _spi->endTransaction();


}

void TFT_Driver::setWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {

    _spi -> beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

    // X axis set
    sendCommand(CASET);       
    sendData(x1 >> 8);        // Origin X MSB
    sendData(x1 & 0xFF);      // Origin X LSB
    sendData(x2 >> 8);        // End X MSB
    sendData(x2 & 0xFF);      // End X LSB

    // Y axis set
    sendCommand(RASET);       
    sendData(y1 >> 8);        // Origin Y MSB
    sendData(y1 & 0xFF);      // Origin Y LSB
    sendData(y2 >> 8);        // End Y MSB
    sendData(y2 & 0xFF);      // End Y LSB

    _spi->endTransaction();
}


void TFT_Driver::fillScreen(uint16_t color,uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){

    setWindow(x1,y1,x2,y2);

    _spi -> beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

    sendCommand(RAMWR);

    digitalWrite(_dc, HIGH);

    for (uint32_t i = 0; i < (x2-x1+1)*(y2-y1+1); i++) {
        _spi->write16(color); // 16 bitlik veriyi tek seferde, cevap beklemeden bas!
    }

    _spi->endTransaction();
}