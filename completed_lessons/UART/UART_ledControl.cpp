#include <Arduino.h>

#define LED_PIN 2

unsigned long Time = 0 ;
unsigned long WaitingTime = 1000 ;

char lineBuffer[32];
int lineIndex = 0;

void setup() {

  pinMode(LED_PIN, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("Serial Initialized");

}
void loop() {
 
  char c;
  unsigned long CurrentTime = millis();

    if (Serial.available() != 0){
      c = Serial.read();
      Serial.write(c);

      if (c == '\n'){
        lineBuffer[lineIndex] = '\0';
        if(strcmp(lineBuffer, "LED ON") ==0){
          digitalWrite(LED_PIN, HIGH);
          Serial.println("LED turned ON");
        }
        else if(strcmp(lineBuffer, "LED OFF") ==0){
          digitalWrite(LED_PIN, LOW);
          Serial.println("LED turned OFF");
        }
        else if(strcmp(lineBuffer, "status") == 0){
          Serial.print("System Time: ");
          Serial.println(CurrentTime);
        }
        Serial.print("You typed: ");
        Serial.println(lineBuffer);
        lineIndex = 0;
      }
      else if (c != '\r'){
        lineBuffer[lineIndex] = c;
        lineIndex++;
        if(lineIndex >= sizeof(lineBuffer) - 1){
          lineIndex = sizeof(lineBuffer) - 2;
        }

      }
    }

}
