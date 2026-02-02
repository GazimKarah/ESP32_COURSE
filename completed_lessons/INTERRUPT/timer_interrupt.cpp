#include <Arduino.h>
#include "driver/gpio.h"
#include "esp32-hal-timer.h"  

#define LED_PIN 2


#define TIMER_DIVIDER 80  //  Hardware timer clock divider

void IRAM_ATTR onTimer();

hw_timer_t *My_timer = NULL;

void setup() {

  Serial.begin(115200);
  pinMode (LED_PIN, OUTPUT);

  My_timer = timerBegin(0, TIMER_DIVIDER, true ); //timer 0, prescaler 80, count up
  timerAttachInterrupt(My_timer, &onTimer,true); //attach onTimer function to timer
  timerAlarmWrite(My_timer, 1000000, true); //1 second alarm, auto-reload true
  timerAlarmEnable(My_timer); //enable alarm
}

void loop() {
 


}

void IRAM_ATTR onTimer(){

  digitalWrite (LED_PIN, !digitalRead(LED_PIN));

}