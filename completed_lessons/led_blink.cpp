#include <Arduino.h>

#define LED_PIN 2

unsigned long Time = 0 ;
unsigned long WaitingTime = 1000 ;

void setup() {

  pinMode(LED_PIN, OUTPUT);

}
void loop() {
 
  char c;
  unsigned long CurrentTime = millis();

    if (CurrentTime - Time >=  WaitingTime){
      Time = CurrentTime;
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }
}
