#include <Arduino.h>

#define LEDC_CHANNEL_0 0
#define LEDC_TIMER_BIT 8
#define LEDC_BASE_FREQ 5000
#define LEDC_PWM_PIN 18

#define POT_PIN 34

#define TIMER_DIVIDER 80 // 80 MHZ / 80 = 1MHZ (1 tick = 1us)
#define SAMPLING_RATE 2000 // 2000 tick = 2ms (500hz sampling rate)

hw_timer_t *adc_timer = NULL;

void IRAM_ATTR adcTimer();

// ------------ Filter plan for esp32 adc problem -----------------
// formula: y[n] = (1-alpha) * y[n-1] + alpha*x[n] ; (0 < alpha < 1)

#define FILTER_ALPHA 0.45f

// Simulink graphic with uart
// 20ms (50hz)
#define SERIAL_SEND_INTERVAL 20

volatile int pwm_out = 0;
volatile float filtered_val = 0;
unsigned long lastSerialTime = 0;

volatile bool adc_flag = false;

void setup() {

  Serial.begin(115200);
  

  //PWM init
  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
  ledcAttachPin(LEDC_PWM_PIN, LEDC_CHANNEL_0);

  //ADC init
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  adc_timer = timerBegin(0, TIMER_DIVIDER, true);
  timerAttachInterrupt(adc_timer, &adcTimer,true); //attach onTimer function to timer
  timerAlarmWrite(adc_timer, SAMPLING_RATE, true); //2ms alarm, auto-reload true
  timerAlarmEnable(adc_timer); //enable alarm

  
}
void loop() {
  
  if (adc_flag == true){

    //Reading the ADC
    int raw_val = analogRead(POT_PIN);

    //Filter it
    filtered_val = (FILTER_ALPHA * raw_val) + ((1.0f - FILTER_ALPHA) * filtered_val);

    //Mapping 12 bit ADC to 8 bit PWM (bit shifting: 4096 / 16 = 256)
    int temp_val = (int)filtered_val >> 4;


    //Actuation with safety clamping
    if (temp_val > 255) temp_val = 255;
    if (temp_val <  0) temp_val = 0;

    pwm_out = temp_val;
    
    ledcWrite(LEDC_CHANNEL_0, pwm_out);

    adc_flag = false;

  }

  if (millis() - lastSerialTime > SERIAL_SEND_INTERVAL) {
    lastSerialTime = millis();
    Serial.write(pwm_out);
  }

}

void IRAM_ATTR adcTimer(){

  adc_flag = true;

}