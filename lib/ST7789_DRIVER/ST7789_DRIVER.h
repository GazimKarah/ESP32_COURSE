#ifndef ST7789_DRIVER_H

#define ST7789_DRIVER_H


#include <Wire.h>
#include <Arduino.h>
#include "SPI.h"

// ST7789 Connections
// Vcc - 3v3
// GND - GND
// SCL - GPIO 18
// SDA - GPIO 23
// RES - GPIO 4 (Reset Pin)
// DC - GPIO 2 (data/command)
// BLK (Backlight) -  3v3 (temporary)

// ST7789 FUNCTIONS
// SWRESET (Software Reset) (01h) | SLPOUT (sleep out) (11h / 0b00010001) | COLMOD (interface pixel format) (3Ah / 0b00111010)
// DISPON (display on) (29h / 0b00101001) | CASET (Coulm Address Set) (2Ah / 0b00101010) | RASET (Row Address Set) (2Bh / 0b00101011)
// RAMWR (Memort Write) (2Ch / 0b00101100)

//For init sequence: SWRESET -> SLPOUT -> COLMOD -> DISPON
//Then, this example's algorithm: CASET -> RASET -> RAMWR

// Constant definitions for TFT Screen commands
#define SWRESET 0x01
#define SLPOUT 0x11
#define COLMOD 0x3A
#define DISPON 0x29
#define CASET 0x2A
#define RASET 0x2B
#define RAMWR 0x2C

    class TFT_Driver
    {

        private:

            SPIClass *_spi;
            uint8_t _dc;
            uint8_t _rst;

            void sendCommand(uint8_t command);
            void sendData(uint8_t data);

        public:

            TFT_Driver(SPIClass* spi_bus, uint8_t dc_pin, uint8_t rst_pin);

            void init();

            void setWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
            void fillScreen(uint16_t color,uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

    };


#endif