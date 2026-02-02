#include <Arduino.h>

#define LED_PIN 2

// Zamanlayıcı Değişkenleri
unsigned long Time = 0;
unsigned long WaitingTime = 1000; // Varsayılan: 1 saniye

// CLI (Buffer) Değişkenleri
char lineBuffer[32];
int lineIndex = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("\n--- CLI System Initialized ---");
  Serial.println("Commands: 'led on', 'led off', 'period <ms>', 'status'");
}

void loop() {
  char c;
  unsigned long CurrentTime = millis();

  // --- 1. GÖREV: Non-Blocking Blink (Zamanlayıcı) ---
  if (CurrentTime - Time >= WaitingTime) {
    Time = CurrentTime;
    digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // LED'i tersle
  }

  // --- 2. GÖREV: CLI (Komut Okuma) ---
  if (Serial.available() != 0) {
    c = Serial.read();

    // A. ENTER TUSU (Komutu İşle)
    if (c == '\n') {
      Serial.println(); // Alt satıra geç
      lineBuffer[lineIndex] = '\0'; // String'i kapat
      
      // Komut: period <sayı>
      if (strncmp(lineBuffer, "period ", 7) == 0) {
        WaitingTime = atoi(&lineBuffer[7]); // 7. adresten sonrasını sayıya çevir
        Serial.print(">> OK: Period set to ");
        Serial.print(WaitingTime);
        Serial.println(" ms");
      }
      // Komut: led on
      else if (strcmp(lineBuffer, "led on") == 0) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println(">> OK: LED Force ON");
        // Not: Blink devam eder ama LED HIGH başlar. 
        // Tamamen durdurmak istersen WaitingTime logic'ini değiştirmek gerekir.
      }
      // Komut: led off
      else if (strcmp(lineBuffer, "led off") == 0) {
        digitalWrite(LED_PIN, LOW);
        Serial.println(">> OK: LED Force OFF");
      }
      // Komut: status
      else if (strcmp(lineBuffer, "status") == 0) {
        Serial.print(">> SYSTEM STATUS: Uptime=");
        Serial.print(millis());
        Serial.print(" ms, Period=");
        Serial.print(WaitingTime);
        Serial.println(" ms");
      }
      // Hatalı Komut
      else {
        Serial.print(">> ERROR: Unknown command [");
        Serial.print(lineBuffer);
        Serial.println("]");
      }
      
      lineIndex = 0; // Buffer'ı sıfırla
    }

    // B. BACKSPACE (Silme)
    else if (c == '\b' || c == 127) {
      if (lineIndex > 0) {
        lineIndex--;
        lineBuffer[lineIndex] = '\0';
        Serial.print("\b \b"); // Ekranda görsel silme
      }
    }

    // C. NORMAL KARAKTER (Kaydet ve Ekrana Bas)
    else if (c != '\r') {
      Serial.write(c); // <--- ECHO (Ekrana bas)
      
      lineBuffer[lineIndex] = c;
      lineIndex++;
      
      // Buffer Taşma Kontrolü
      if (lineIndex >= sizeof(lineBuffer) - 1) {
        lineIndex = sizeof(lineBuffer) - 2; 
      }
    }
  }
}