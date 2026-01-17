# Ders 1.1: Non-Blocking Blink

## 1. Amaç
Bu modül, işlemciyi durdurmadan (blocking delay kullanmadan) zaman yönetimi yapmayı ve "Super Loop" mimarisini kavramayı amaçlar.

## 2. Donanım Konfigürasyonu
* **MCU:** ESP32 devkit v1
* **Periferikler:** Dahili LED (GPIO 2 )

## 3. Yazılım Mimarisi
* **Framework:** Arduino
* **Yöntem:** `millis()` tabanlı zaman farkı kontrolü.

## 4. Test ve Doğrulama
* [X] Kod derleniyor ve karta yükleniyor.
* [X] LED, `delay()` kullanılmadan belirlenen periyotta yanıp sönüyor.
* [X] Buton/Sistem etkileşimi sırasında LED donmuyor.

## 5. Notlar
* SysTick mekanizması Arduino `millis()` fonksiyonu ile soyutlanmıştır.

## Ders 1.3: CLI (Komut Satırı Arayüzü) - Temel
* **Amaç:** UART üzerinden gelen veriyi karakter karakter toplamak ve anlamlı bir komut satırı (String) oluşturmak.
* **Kazanımlar:**
    * `buffer` ve `lineBuffer` farkı (Taşıma vs. Anlamlandırma).
    * `\n` (Newline) karakteri ile paket sonu tespiti.
    * Null Terminator (`\0`) önemi.
* **Durum:**
    * [x] Echo (Yazılanın geri gelmesi) çalışıyor.
    * [x] Enter'a basınca satırın tamamlanması çalışıyor.
    * [ ] Komutların işlenmesi (Parsing) [Sırada]