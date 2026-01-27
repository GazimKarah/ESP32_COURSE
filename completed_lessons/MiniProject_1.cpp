#include <Arduino.h>

#define LED_PIN 2
#define interrupt_PIN 18 // GPIO pin for the button
uint8_t led_status =0;

unsigned long Time = 0 ;
unsigned long WaitingTime = 1000;

char lineBuffer[32];
int lineIndex = 0;

void setup() {

  Serial.begin(115200);
  pinMode (LED_PIN, OUTPUT);
  pinMode (interrupt_PIN, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt (interrupt_PIN), blink_and_count, FALLING);
 

}
void loop() {
 
  while(1){
    // Do nothing, everything is handled in the interrupt
  }
}

void blink_and_count(){

  static int count = 0;
  digitalWrite(LED_PIN, !led_status); 
  led_status = !led_status;
  count++;
  Serial.println(count);  
}