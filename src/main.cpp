#include <Arduino.h>

#define LED_PIN 2
#define interrupt_PIN 18 // GPIO pin for the button
volatile bool toogleReq = false;
volatile uint32_t count =0;


void IRAM_ATTR blink_and_count();

void setup() {

  Serial.begin(115200);
  Serial.println("Interrupt Example Started");
  pinMode (LED_PIN, OUTPUT);
  pinMode (interrupt_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt (interrupt_PIN), blink_and_count , FALLING);
 

}
void loop() {
 
    if (toogleReq){
      digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED state
      Serial.print("Button pressed ");
      Serial.print(count);
      Serial.println(" times");
      toogleReq = false;
    }
}

void IRAM_ATTR blink_and_count(){
  count++;
  toogleReq = !toogleReq; 
}