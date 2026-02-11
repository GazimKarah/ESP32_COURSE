#include <Arduino.h>
#include <Wire.h> // I2C Library

#include "LCD_DRIVER.h"

#define led_pin 2
#define lcd_adress 0x27 // I2C address of the LCD

// Uart Protocol [HEAD][LEN][CMD][DATA][CRC]

#define HEADER 0xFE
#define MAX_PACKAGE_SIZE 64

#define CMD_LCD_WRITE 0xB1
#define CMD_LED_CTRL 0xA2

char c;

//Enum defines integer value.
typedef enum {
  ST_IDLE,  // 0: Waiting for Header
  ST_LEN,   // 1: Waiting for Length information
  ST_CMD,   // 2: Waiting for Command
  ST_DATA,  // 3: Waiting for Data
  ST_CRC    // 4: Verifying (checksum/crc)
} ParserState;



ParserState current_state = ST_IDLE;
// Variables
uint8_t package_len = 0;
uint8_t package_cmd = 0;
uint8_t package_data[64]; 
uint8_t data_index = 0;
uint8_t calc_crc = 0;

LCD_DRIVER lcd(lcd_adress);

// Function Declaration

void execute_command();
void parse_byte(uint8_t rx);




void setup() {

  Serial.begin(115200);
  Wire.begin();
  pinMode(led_pin, OUTPUT);

  lcd.init();
  lcd.clear();
  lcd.set_cursor(0,0);
  lcd.print_string("UART Terminal:");
  Serial.println(" ");
  Serial.print("Waiting Data: ");

}
void loop() {
  

  while (Serial.available()){

    c = Serial.read();
    parse_byte(c);

  }

}

void execute_command(){

  Serial.println("-> Package valid! Execution has been started...");

  if (package_cmd == CMD_LCD_WRITE) {

    lcd.clear();
    lcd.set_cursor(1,0);
    
    package_data[package_len] = '\0';
    lcd.print_string((char*)package_data);

    Serial.println("Printed to LCD: ");
    Serial.print((char*)package_data);

  }

  else if (package_cmd == CMD_LED_CTRL){

    if(package_data[0] >= 1 ){

      digitalWrite(led_pin, HIGH);

    }
    
    else {

      digitalWrite(led_pin, LOW);

    }

    Serial.println("LED state has been changed.");

  }

}



void parse_byte(uint8_t rx){  //this function processes 1 byte at a time

  switch (current_state){

    case ST_IDLE:
      if(rx == HEADER){

        current_state = ST_LEN;
        calc_crc =0;

      }

    break;

    case ST_LEN:

      package_len = rx;
      calc_crc += rx;
      current_state = ST_CMD;

    break;

    case ST_CMD:

      package_cmd = rx;
      calc_crc += rx;

      data_index = 0;

      if (package_len > 0){
        current_state = ST_DATA;
      }
      else {
        current_state = ST_CRC;
      }

    break;

    case ST_DATA:

      package_data [data_index]=rx;
      calc_crc += rx;
      data_index++;
      
      if(data_index >= package_len){

        current_state = ST_CRC;

      }

    break;

    case ST_CRC:

      if( rx == calc_crc){

        execute_command();
      }

      else {

        Serial.println("Err: CRC isn't matched");
        Serial.println("Received: "); Serial.print(rx,HEX);
        Serial.println("Calculated: "); Serial.print(calc_crc, HEX);

      }
      
      current_state = ST_IDLE;

      break;

  }


}