#ifndef LCD_DRIVER_H

#include <Wire.h>
#include <Arduino.h>

/*PCF8574   → LCD
----------------
P0        → RS
P1        → RW (It can be fixed to GND on most boards)
P2        → E
P3        → Backlight
P4        → D4
P5        → D5
P6        → D6
P7        → D7
*/

// Constant definitions for LCD commands and flags
#define LCD_CMD_MODE 0
#define LCD_DATA_MODE 1
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE 0x04
#define LCD_WIDTH 16

#define LCD_DRIVER_H

    class LCD_DRIVER {

        private: 

            uint8_t lcd_address; //i2c address of the LCD
            void send_nibble(uint8_t nibble, uint8_t mode);
            void send_byte(uint8_t byte, uint8_t mode);
            void pulse_enable(uint8_t data);
            void Update_flag(uint8_t flag, bool state);

        public:

            LCD_DRIVER(uint8_t address);

            void init();
            void print_char(char c);
            void print_string(const char* str);
            void clear();
            void set_cursor(uint8_t row, uint8_t col);
            void display_on();
            void display_off();
            void cursor_on();
            void cursor_off();
            void blink_on();
            void blink_off();
    };

#endif