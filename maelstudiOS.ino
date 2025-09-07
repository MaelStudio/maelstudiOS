#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <lvgl.h>
#define USE_TFT_ESPI_LIBRARY
#include "lv_xiao_round_screen.h"
#include "I2C_BM8563.h"
#include <Adafruit_BMP280.h>
#include "ui.h"
#include "actions.h"

#define HAPTIC_PIN 41

// Haptic motor
unsigned long hapticEnd = 0;
bool hapticActive = false;

// RTC
I2C_BM8563 rtc(I2C_BM8563_DEFAULT_ADDRESS, Wire);
I2C_BM8563_DateTypeDef rtcDate;
I2C_BM8563_TimeTypeDef rtcTime;
const char* days[] = {"Lun", "Mar", "Mer", "Jeu", "Ven", "Sam", "Dim"};

// BMP280
#define SEA_LEVEL_HPA 1005.00
#define BMP_ADDRESS 0x77
Adafruit_BMP280 bmp;

// BATTERY
#define NUM_ADC_SAMPLE 20           // Sampling frequency
#define BATTERY_DEFICIT_VOL 1400    // Battery voltage value at loss of charge (mV)
#define BATTERY_FULL_VOL 2030       // Battery voltage value at full charge (mV)

#define SECOND_ANGLE 3600.0 / 60.0
#define MINUTE_ANGLE 3600.0 / 60.0
#define HOUR_ANGLE   3600.0 / 12.0
#define MONTH_ANGLE  3600.0 / 12.0

void setup() {
  Serial.begin(115200);
  
  // Initialize display
  lv_init();
  lv_xiao_disp_init();
  lv_xiao_touch_init();
  ui_init();

  // Haptic
  pinMode(HAPTIC_PIN, OUTPUT);

  // RTC
  Wire.begin();
  rtc.begin();

  // BMP280
  bmp.begin(BMP_ADDRESS);
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_1);   /* Standby time. */

  // ADC
  analogReadResolution(12);
}

void loop() {
  static unsigned long millisAtLastTick = 0;
  static int lastSecond = -1;

  // Read current RTC time
  rtc.getDate(&rtcDate);
  rtc.getTime(&rtcTime);

  // Keep track of millis offset inside the current second
  unsigned long now = millis();
  if (rtcTime.seconds != lastSecond) {
    // New tick from RTC
    lastSecond = rtcTime.seconds;
    millisAtLastTick = now;
  }
  float secFraction = (now - millisAtLastTick) / 1000.0;
  if (secFraction > 1.0) secFraction = 1.0;

  // Update time and date labels
  lv_label_set_text_fmt(objects.digital_time, "%02i:%02i", rtcTime.hours, rtcTime.minutes);
  lv_label_set_text(objects.day_of_week, days[rtcDate.weekDay]);
  lv_label_set_text_fmt(objects.date, "%02i", rtcDate.date);

  // Update watch hands
  int hour_angle = (rtcTime.hours % 12)*HOUR_ANGLE + rtcTime.minutes*HOUR_ANGLE/60.0 + rtcTime.seconds*HOUR_ANGLE/3600.0;
  int minute_angle = rtcTime.minutes*MINUTE_ANGLE + rtcTime.seconds*MINUTE_ANGLE/60.0;
  int second_angle = (rtcTime.seconds + secFraction)*SECOND_ANGLE;

  lv_img_set_angle(objects.hour_hand, hour_angle);
  lv_img_set_angle(objects.hour_hand_shadow, hour_angle);
  lv_img_set_angle(objects.minute_hand, minute_angle);
  lv_img_set_angle(objects.minute_hand_shadow, minute_angle);
  lv_img_set_angle(objects.second_hand, second_angle);
  lv_img_set_angle(objects.second_hand_shadow, second_angle);

  lv_img_set_angle(objects.month_marker, (rtcDate.month-1)*MONTH_ANGLE);


  // BMP280
  float temperature = bmp.readTemperature(); // *C
  float pressure = bmp.readPressure() / 100.0; // hPa
  float altitude = bmp.readAltitude(SEA_LEVEL_HPA); // m
  int angle = map(temperature, -20, 30, -1200, 1200); // Calculate dial hand angle
  lv_img_set_angle(objects.temperature_hand, angle);
  lv_img_set_angle(objects.temperature_hand_shadow, angle);
  char buf[6];
  sprintf(buf, "%.0f°", temperature);
  lv_label_set_text(objects.temperature, buf);

  // BATTERY DIAL
  int level = batteryLevel();
  lv_label_set_text_fmt(objects.battery_voltage, "%i%", level);
  angle = map(level, 0, 100, -1200, 1200);
  lv_img_set_angle(objects.battery_hand, angle);
  lv_img_set_angle(objects.battery_hand_shadow, angle);

  // Vibration
  updateVibration();

  // Update UI
  lv_timer_handler();
  ui_tick();
}

void vibrate(int duration = 10) {
  digitalWrite(HAPTIC_PIN, HIGH);
  hapticEnd = millis() + duration;
  hapticActive = true;
}

void updateVibration() {
  if (hapticActive && millis() >= hapticEnd) {
    digitalWrite(HAPTIC_PIN, LOW);
    hapticActive = false;
  }
}

int batteryLevel(void) { // in percentage
  int mVolts = 0;
  for(int8_t i=0; i<NUM_ADC_SAMPLE; i++){
    mVolts += analogReadMilliVolts(D0);
  }
  mVolts /= NUM_ADC_SAMPLE;
  int level = map(mVolts, BATTERY_DEFICIT_VOL, BATTERY_FULL_VOL, 0, 100);
  level = (level < 0) ? 0 : ((level > 100) ? 100 : level);
  return level;
}