#include <Arduino.h>

#define LED_PIN 2

unsigned long Time = 0 ;
unsigned long WaitingTime = 1000;

char lineBuffer[32];
int lineIndex = 0;

void setup() {

  pinMode(LED_PIN, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("\n Serial Initialized and LED Period set to 1000 ms");

}
void loop() {
 
  char c;
  unsigned long CurrentTime = millis();


    if (Serial.available() != 0){
      c = Serial.read();
      
      if (c == '\n'){
        Serial.println(); // Echo newline
        lineBuffer[lineIndex] = '\0';
        if(strncmp(lineBuffer, "period " , 7) ==0){
          WaitingTime = atoi(&lineBuffer[7]);
          Serial.println("Period set to " + String(WaitingTime) + " ms");
        }
        else {
          Serial.println("Unknown Command");
        }
        lineIndex = 0;
      }

      else if (c == '\b' || c == 127){
        if(lineIndex > 0){
          lineIndex--;
          lineBuffer[lineIndex] = '\0';  // Null-terminate the string that means the phrase has came to an end
          Serial.print("\b \b"); // Move cursor back, print space, move cursor back again
        }
      }
      else if (c != '\r'){
        Serial.write(c); // Echo back the received character
        
        lineBuffer[lineIndex] = c;
        lineIndex++;
        if(lineIndex >= sizeof(lineBuffer) - 1){
          lineIndex = sizeof(lineBuffer) - 2;
        }

      }
    }
    if (CurrentTime - Time >=  WaitingTime){
      Time = CurrentTime;
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }
}
