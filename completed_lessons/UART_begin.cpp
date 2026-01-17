#include <Arduino.h>

#define LED_PIN 2

unsigned long Time = 0 ;
unsigned long WaitingTime = 1000 ;


char buffer[64];
int tail = 0, head = 0;

void setup() {

  pinMode(LED_PIN, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("Serial Initialized");

}
void loop() {
 

  unsigned long CurrentTime = millis();

    if (CurrentTime - Time >=  WaitingTime){
      Time = CurrentTime;
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }

    if(Serial.available() != 0){

      buffer[head] = Serial.read();
      
      if(buffer[head] == '\n' ){
        buffer[head] = '\0';
        Serial.print(buffer);
        head = 0;
        tail = 0;
      }
      else if(buffer[head] != '\n'){
      head = (head + 1) % sizeof(buffer); 
      }

    }
    if (tail != head){
      Serial.print(buffer[tail]);
      tail = (tail + 1) % sizeof(buffer);
    }
}
