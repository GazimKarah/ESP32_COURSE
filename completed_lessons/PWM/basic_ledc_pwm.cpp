#include <Arduino.h>

#define LEDC_CHANNEL_0 0
#define LEDC_TIMER_BIT 8
#define LEDC_BASE_FREQ 5000
#define LEDC_PWM_PIN 18


void setup() {

  Serial.begin(115200);
  Serial.write("Uart has begun...");

  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
  ledcAttachPin(LEDC_PWM_PIN, LEDC_CHANNEL_0);

  ledcWrite(0,128);
  
}
void loop() {
  // Boş döngü
}

