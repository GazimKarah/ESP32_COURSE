#include <Arduino.h>

#define LED_PIN 2

unsigned long Time = 0 ;
unsigned long WaitingTime = 1000;

char lineBuffer[32];
int lineIndex = 0;
bool overflowed = false;
bool handled = false;

unsigned long parseMs(const char* s, bool* ok);
bool AllDigits(const char* s);

void setup() {

  pinMode(LED_PIN, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("\n Serial Initialized and LED Period set to 1000 ms");

}

void loop() {
 
  char c;
  unsigned long CurrentTime = millis();

  while (Serial.available() != 0) {

    c = Serial.read();

    if (overflowed == true) {

        
        if(c == '\n' || c == '\r') {

            overflowed = false;
            lineIndex = 0;
            lineBuffer[0] = '\0';
            Serial.println();
            Serial.println("ERR: Input Overflow.");
            continue;

        }
        continue;
    }

    else {

        Serial.write(c); // Echo back the received character

        if (c == '\b' || c == 127){

            if(lineIndex > 0){
                lineIndex--;
                lineBuffer[lineIndex] = '\0';  // Null-terminate the string that means the phrase has came to an end
                Serial.print("\b \b"); // Move cursor back, print space, move cursor back again
            }
        }
        
        else if (c == '\n' || c == '\r') {

            handled = false;
            Serial.println(); // Echo newline
            lineBuffer[lineIndex] = '\0';

            if(strncmp(lineBuffer, "period" , 6) ==0){
            // Is "period" command
                if(lineBuffer[6] == '\0' || lineBuffer[6] == ' '){
                    char* arg = &lineBuffer[6]; // Pointer to the argument part
                while (*arg == ' ') arg++; // Skip spaces
                   
                if(*arg == '\0'){
                    Serial.println("ERR: Missing Number Argument.");
                    handled = true;
                }
                else if(!AllDigits(arg)){

                    Serial.println("ERR: Invalid Number Argument.");
                    handled = true;
                }
                else {
                    bool ok = false;

                    unsigned long period = parseMs(arg, &ok);

                    const unsigned long MIN_PERIOD = 10; // 10 ms
                    const unsigned long MAX_PERIOD = 60000; // 60 seconds

                    if(!ok){
                        Serial.println("ERR: Invalid Number Argument.");
                    }
                    else if (period < MIN_PERIOD || period > MAX_PERIOD){
                        Serial.println("ERR: Period Out Of Range. Must be between " + String(MIN_PERIOD) + " ms and " + String(MAX_PERIOD) + " ms.");
                    }
                    else{
                        WaitingTime = period;
                        Serial.println("Period set to " + String(WaitingTime) + " ms");
                    }
                    handled = true;
                    }
                }



            }

            else if (handled == false){
            
                Serial.println("Unknown Command");

            }
            else{
                // Command was handled successfully
                if(lineIndex < sizeof(lineBuffer) - 1){
                    lineBuffer[lineIndex++] = c;
                    lineBuffer[lineIndex] = '\0'; // Null-terminate the string
                    Serial.write(c); // Echo back the received character

                }
                else {
                    overflowed = true;
                    continue;
                }
            
            }
            
        }



    }

    if (CurrentTime - Time >= WaitingTime){

      Time = CurrentTime;
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    
    }

}
unsigned long parseMs(const char* s, bool* ok){ // Parses a string to extract an unsigned long representing milliseconds

    char* endptr = nullptr; // Pointer to track where parsing stopped
    unsigned long value = strtoul(s, &endptr, 10); // Convert string to unsigned long
    *ok = (endptr != s) && (*endptr == '\0'); // Check if parsing was successful and consumed the entire string
    return value;
}

bool AllDigits(const char* s){
    if (*s == '\0') return false; // Empty string check
    while (*s) {
        if (*s < '0' || *s > '9') return false; // Non-digit character found (We check ASCII values here ('0' = 48, '9' = 57)  and if it is outside this range, it is not a digit)
        s++; // Move to the next character (\0 is essential for the loop termination if we do not place it end of the word, it will continue reading garbage values in memory))
        
    }
    return true; // All characters are digits
}