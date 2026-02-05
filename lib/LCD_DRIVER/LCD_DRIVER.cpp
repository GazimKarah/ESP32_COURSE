#include "LCD_DRIVER.h"

LCD_DRIVER::LCD_DRIVER(uint8_t address) {


    lcd_address = address;

}

void LCD_DRIVER::pulse_enable(uint8_t data)
{
    // Code to pulse the enable pin
    Wire.beginTransmission(lcd_address);
    Wire.write(data & ~LCD_ENABLE);
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

    uint8_t packet = (nibble << 4) & 0xF0; // Shift nibble to higher bits
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

void LCD_DRIVER::Update_flag(uint8_t flag, bool state)
{
    static uint8_t display_control = 0x08; // Display control mandatory bit
    // 0x04 Display ON/OFF control bit
    // 0x02 Cursor ON/OFF control bit
    // 0x01 Blinking ON/OFF control bit

    send_byte(display_control | flag, LCD_CMD_MODE);
}

void LCD_DRIVER::init()
{
    // Initialization code for the LCD
    delay(50); // Wait for LCD to power up
    send_nibble(0x03, LCD_CMD_MODE);
    delay(5);
    send_nibble(0x03, LCD_CMD_MODE); 
    delayMicroseconds(150);
    
    send_nibble(0x03, LCD_CMD_MODE);
    delayMicroseconds(150);

    send_nibble(0x02, LCD_CMD_MODE);
    delayMicroseconds(50);

    send_nibble(0x02, LCD_CMD_MODE); // Function Set: 4-bit mode
    send_nibble(0x08, LCD_CMD_MODE);

    send_nibble(0x00, LCD_CMD_MODE); // Display ON
    send_nibble(0x0C, LCD_CMD_MODE);

    send_nibble(0x00, LCD_CMD_MODE); // Display Clear
    send_nibble(0x01, LCD_CMD_MODE);
    delay(2);

    send_nibble(0x00, LCD_CMD_MODE); // Entry Mode Set
    send_nibble(0x06, LCD_CMD_MODE);
    delay(5);
}

void LCD_DRIVER::print_char(char c)
{
    // Code to print a character on the LCD
    send_byte((uint8_t)c, LCD_DATA_MODE);
}

void LCD_DRIVER::print_string(const char* str)
{
    int count = 0;
    // Code to print a string on the LCD
    while (*str !='\0' && count < 16){
        count++;
        print_char(*str);
        str++;
    }
}
void LCD_DRIVER::clear()
{
    // Code to clear the LCD display
    send_byte(0x01, LCD_CMD_MODE); 
    delay(2); // Clear command needs >1.52ms to settle

}

void LCD_DRIVER::set_cursor(uint8_t row, uint8_t col)
{
    // Code to set the cursor position on the LCD
    uint8_t row_offsets[] = {0x00, 0x40};

    if(row >= 1) row = 1; // Limit to 2 rows
    else { row = 0; } // Default to row 0 if invalid

    if(col >= 15) col = 15; // Limit to 16 columns
    else { col = 0; } // Default to column 0 if invalid

    uint8_t position = col + row_offsets[row];

    send_byte(0x80 | position, LCD_CMD_MODE); // Set DDRAM address

}

void LCD_DRIVER::display_on()
{
    // Code to turn on the display
    Update_flag (0x04,true);
}
void LCD_DRIVER::display_off(){
    // Code to turn off the display
    Update_flag (0x04,false);
}
void LCD_DRIVER::cursor_on(){
    // Code to turn on the cursor
    Update_flag (0x02,true);
}
void LCD_DRIVER::cursor_off(){
    // Code to turn off the cursor
    Update_flag (0x02,false);
}
void LCD_DRIVER::blink_on(){
    // Code to turn on blinking cursor
    Update_flag (0x01,true);
}
void LCD_DRIVER::blink_off(){
    // Code to turn off blinking cursor
    Update_flag (0x01,false);
}