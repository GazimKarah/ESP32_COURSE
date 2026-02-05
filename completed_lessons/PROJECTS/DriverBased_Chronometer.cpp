#include <Arduino.h>
#include <Wire.h> // I2C Library

#include "LCD_DRIVER.h"

#define lcd_adress 0x27 // I2C address of the LCD
#define interrupt_PIN 18 // GPIO pin for the button
#define TIMER_DIVIDER 80  //  Hardware timer clock divider

static volatile unsigned long lastInterruptTime = 0;
static volatile uint32_t debounce = 200000; // 200ms Debounce period
volatile unsigned long counter = 0;
volatile bool start_stop_flag = false;

void display_time(unsigned long ms_value);

void IRAM_ATTR onTimer();
void IRAM_ATTR start_stop();

hw_timer_t *Chronometer_timer = NULL;
LCD_DRIVER lcd(lcd_adress);


void setup() {
  
  pinMode(interrupt_PIN,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_PIN),start_stop,FALLING);

  Chronometer_timer = timerBegin(0, TIMER_DIVIDER, true ); //timer 0, prescaler 80, count up
  timerAttachInterrupt(Chronometer_timer, &onTimer,true); //attach onTimer function to timer
  timerAlarmWrite(Chronometer_timer, 1000, true); //1ms alarm value, autoreload true
  timerAlarmEnable(Chronometer_timer); //enable alarm
  

  Serial.begin(115200);
  while (!Serial); // wait for Serial to be ready
  Serial.println("\nStarting I2C LCD");
  Wire.begin();
  
  lcd.init();
  lcd.clear();
  lcd.set_cursor(0, 0); // row 0, column 0
  lcd.print_string("Chronometer:");
  lcd.set_cursor(1,0);
  lcd.print_string("00:00:00:000");
  
}
void loop() {
  
  if(start_stop_flag == true){

    display_time(counter);


  }

}

void display_time(unsigned long ms_value){
  uint16_t ms = (ms_value % 1000);
  uint8_t sn = (ms_value / 1000) % 60;
  uint8_t dk = (ms_value / 60000) % 60;
  uint8_t sa = (ms_value / 3600000);
  
  if(sa >= 24){

    sa = 0;
    
  }

  char time_buffer[16];

  snprintf(time_buffer, sizeof(time_buffer),"%02d:%02d:%02d:%03d",sa,dk,sn,ms);

  lcd.set_cursor(1,0);
  lcd.print_string(time_buffer);

}

void IRAM_ATTR onTimer(){

  if (start_stop_flag == true){
    counter++;
  }
}
void IRAM_ATTR start_stop(){

  uint32_t now = (uint32_t)micros();
  uint32_t dt = now - lastInterruptTime;

  if (dt<debounce){
    
    // Do nothing and quit isr.
    return;

  }

  start_stop_flag = !start_stop_flag;

}