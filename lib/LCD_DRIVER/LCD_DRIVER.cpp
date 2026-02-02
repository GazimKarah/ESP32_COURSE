#include "LCD_DRIVER.h"

LCD_DRIVER::LCD_DRIVER(uint8_t address) {


    lcd_address = address;

}

void LCD_DRIVER::pulse_enable(uint8_t data)
{
    // Code to pulse the enable pin
    Wire.beginTransmission(lcd_address);
    Wire.write(data | LCD_ENABLE);
    Wire.endTransmission();
    delayMicroseconds(1); // Enable pulse must be >450ns
    Wire.beginTransmission(lcd_address);
    Wire.write(data & ~LCD_ENABLE);
    Wire.endTransmission();
    delayMicroseconds(50); // Commands need >37us to settle
}

void LCD_DRIVER::send_nibble(uint8_t nibble, uint8_t mode)
{
    // Code to send a nibble to the LCD

    uint8_t packet = (nibble << 4) & 0x0F0; // Shift nibble to higher bits
    packet |= LCD_BACKLIGHT; // Turn on backlight
    if (mode == LCD_DATA_MODE){
        packet |= 0x01; // Set RS for data mode
    }
    pulse_enable(packet);
}

void LCD_DRIVER::send_byte(uint8_t byte, uint8_t mode)
{
    // Code to send a byte to the LCD

    uint8_t high_nibble = (byte >> 4) & 0x0F; // In the send_nibble function we shift left, so here we shift right
    uint8_t low_nibble = byte & 0x0F;
    send_nibble(high_nibble, mode);
    send_nibble(low_nibble, mode);
}



void LCD_DRIVER::init()
{
    // Initialization code for the LCD
    delay(50); // Wait for LCD to power up
    send_nibble(0x30, LCD_CMD_MODE);
    delay(5);
    send_nibble(0x20, LCD_CMD_MODE);
    delayMicroseconds(50);
    send_nibble(0x20, LCD_CMD_MODE);
    delayMicroseconds(50);

    send_nibble(0x00, LCD_CMD_MODE); // Display ON
    send_nibble(0xC0, LCD_CMD_MODE);

    send_nibble(0x00, LCD_CMD_MODE); //Display Clear
    send_nibble(0x10, LCD_CMD_MODE);
    delay(2);

    send_nibble(0x60, LCD_CMD_MODE); // Entry Mode Set
    delay(5);
}

void LCD_DRIVER::print_char()
{
    // Code to print a character on the LCD
}
void LCD_DRIVER::print_string()
{
    // Code to print a string on the LCD
}
void LCD_DRIVER::clear()
{
    // Code to clear the LCD display
    send_byte(0x01, LCD_CMD_MODE); 
}
void LCD_DRIVER::set_cursor(uint8_t row, uint8_t col)
{
    // Code to set the cursor position on the LCD
    uint8_t row_offsets[] = {0x00, 0x40};

    uint8_t position = col + row_offsets[row];

    send_byte(0x80 | position, LCD_CMD_MODE); // Set DDRAM address

}
