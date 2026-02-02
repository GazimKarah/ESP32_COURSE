#include <Arduino.h>
#include <Wire.h> // I2C Library

void setup() {
  Wire.begin(); // Start I2C as Master (SDA : GPIO21, SCL : GPIO22)
  
  Serial.begin(115200);
  while (!Serial); // wait for Serial to be ready
  Serial.println("\nI2C Tarayici Baslatiliyor...");
}

void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Taraniyor...");

  nDevices = 0;
  
  // Try all possible i2c adresses between 1 and 127
  for(address = 1; address < 127; address++ ) {
    
    // Check if device responds at this address
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      // If there is a device at this adress
      Serial.print("I2C cihazi bulundu! Adres: 0x");
      if (address < 16) 
        Serial.print("0");
      Serial.print(address, HEX); // Write address in Hexadecimal
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Bilinmeyen hata (Adres 0x");
      if (address < 16) 
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(")");
    }    
  }
  
  if (nDevices == 0)
    Serial.println("Hicbir I2C cihazi bulunamadi.\n");
  else
    Serial.println("Tarama tamamlandi.\n");

  delay(5000); // Wait 5 seconds for next scan
}