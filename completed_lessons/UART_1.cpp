#include <Arduino.h>

#define LED_PIN 2

unsigned long Time = 0 ;
unsigned long WaitingTime = 1000 ;


char buffer[64];
char lineBuffer[32];
int lineIndex = 0;
int tail = 0, head = 0;

void setup() {

  pinMode(LED_PIN, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("Serial Initialized");

}
void loop() {
 
  char c;
  unsigned long CurrentTime = millis();

    if (CurrentTime - Time >=  WaitingTime){
      Time = CurrentTime;
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }

    if (Serial.available() != 0){
      c = Serial.read();
      Serial.write(c);

      if (c == '\n'){
        lineBuffer[lineIndex] = '\0';
        Serial.print("You typed: ");
        Serial.println(lineBuffer);
        lineIndex = 0;
      }
      else {
        lineBuffer[lineIndex] = c;
        lineIndex++;
        if(lineIndex >= sizeof(lineBuffer) - 1){
          lineIndex = sizeof(lineBuffer) - 2;
        }

      }
    }

}
