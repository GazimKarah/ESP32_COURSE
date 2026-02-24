#include <Arduino.h>

#define LEDC_CHANNEL_0 0
#define LEDC_TIMER_BIT 8
#define LEDC_BASE_FREQ 5000
#define LEDC_PWM_PIN 18

#define TIMER_DIVIDER 80

hw_timer_t *LEDC_timer = NULL;

void IRAM_ATTR ledTimer();

volatile int current_duty = 0;
volatile int fadeAmount = 5;

void setup() {

  Serial.begin(115200);
  Serial.write("Uart has begun...");

  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
  ledcAttachPin(LEDC_PWM_PIN, LEDC_CHANNEL_0);

  LEDC_timer = timerBegin(0, TIMER_DIVIDER, true);
  timerAttachInterrupt(LEDC_timer, &ledTimer,true); //attach onTimer function to timer
  timerAlarmWrite(LEDC_timer, 10000, true); //10ms alarm, auto-reload true
  timerAlarmEnable(LEDC_timer); //enable alarm
}
void loop() {
  // Boş döngü
}

void IRAM_ATTR ledTimer(){

  ledcWrite(LEDC_CHANNEL_0, current_duty);

  current_duty = current_duty + fadeAmount;

  if (current_duty <= 0 || current_duty >= 255) {
    fadeAmount = -fadeAmount; // +5 ise -5 olur, -5 ise +5 olur.
  }

}