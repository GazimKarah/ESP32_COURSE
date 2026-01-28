#include <Arduino.h>
#include "driver/gpio.h"

#define LED_PIN 2
#define interrupt_PIN 18 // GPIO pin for the button
volatile bool toggleReq = false;
volatile uint32_t count =0;

// Bouncing diagnosis variables
static volatile unsigned long lastInterruptTime = 0; //last interrupt time
static const uint32_t DEBOUNCE_US = 50000; // 50 ms
volatile uint32_t lastValidInterval = 0;

bool ledState = false;

void IRAM_ATTR blink_and_count();

void setup() {

  Serial.begin(115200);
  Serial.println("Interrupt Example Started");
  pinMode (LED_PIN, OUTPUT);
  pinMode (interrupt_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt (interrupt_PIN), blink_and_count , FALLING);
 

}
void loop() {
 
    if (toggleReq) {
    // küçük kritik bölge: ISR ile çakışmayı azalt
    noInterrupts();
    toggleReq = false;
    uint32_t c = count;
    uint32_t interval = lastValidInterval;
    interrupts();

    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);

    Serial.print("Button pressed ");
    Serial.print(c);
    Serial.print(" times (Interval: ");
    Serial.print(interval);
    Serial.println(" us)");
  }
}

void IRAM_ATTR blink_and_count(){
  uint32_t now = (uint32_t)micros();
  uint32_t dt  = now - lastInterruptTime;

  if (dt < DEBOUNCE_US){
    // Ignore this interrupt as it is within the debounce period
    return;
  }
  
  lastInterruptTime = now ; // Update last interrupt time
  lastValidInterval = dt; // Calculate interval since last interrupt

  count++;
  toggleReq = true; 
}