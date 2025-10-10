#define USE_TFT_ESPI_LIBRARY
#include "lv_xiao_round_screen.h"
#include <SPI.h>
#include <Wire.h>
#include <lvgl.h>
#include "I2C_BM8563.h"
#include "ui.h"
#include "actions.h"
#include "driver/gpio.h"
#include <esp_camera.h>
#include "SD.h"
#include <Preferences.h>
#include "camera.h"

#define sensor_t sensor_t_bmp
#include <Adafruit_Sensor.h>
#undef sensor_t

#include <Adafruit_BMP280.h>

// APPS
enum AppID {
  HOME = -1,
  APP_CAMERA = 0
};
AppID activeApp = HOME;

// Camera app
uint8_t cam_buf[SCREEN_WIDTH * SCREEN_HEIGHT * 2];  // 2 bytes per pixel (RGB565)
static lv_img_dsc_t cam_img_dsc;
bool takingPhoto = false;

// SD
#define SD_CS_PIN D2

// Haptic
#define HAPTIC_PIN 41

// Display
#define BACKLIGHT_PIN D6
#define TOUCH_INT_PIN D7

// Haptic motor
unsigned long hapticEnd = 0;
int hapticDuration = 0;
bool hapticStart = false;
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

// AUTO SLEEP
#define AUTO_SLEEP 20000 // Inactivity time for auto sleep (ms)
unsigned long lastActive = 0;
bool wakeUp = true;

// Preferences
Preferences preferences;

void setup() {
  pinMode(BACKLIGHT_PIN, OUTPUT);
  pinMode(TOUCH_INT_PIN, INPUT_PULLUP);

  preferences.begin("config", false);

  if (preferences.getBool("autoSleepFlag", false)) {
    preferences.putBool("autoSleepFlag", false);
    digitalWrite(BACKLIGHT_PIN, LOW); // Turn off display backlight

    // Enable wakeup on touch pin, GPIO 44 (falling edge)
    gpio_wakeup_enable((gpio_num_t)TOUCH_INT_PIN, GPIO_INTR_LOW_LEVEL);
    esp_sleep_enable_gpio_wakeup();
    esp_light_sleep_start(); // ENTER LIGHT SLEEP

    lastActive = millis();
  }
  
  Serial.begin(115200);

  // Initialize display
  lv_init();
  lv_xiao_disp_init();
  lv_xiao_touch_init();
  ui_init();

  // Initialize SD card
  pinMode(SD_CS_PIN, OUTPUT);
  if(!SD.begin(SD_CS_PIN)){
    Serial.println("Card mount failed");
    while (1) {}
  }

  // Initialize camera
  esp_err_t err = initCam();
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    while (1) {}
  }
  esp_camera_deinit(); // Deinit to save power

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

  // Gesture control
  lv_obj_add_event_cb(objects.watchface, watchfaceSwipe, LV_EVENT_GESTURE, NULL);
  lv_obj_add_event_cb(objects.home, homeSwipe, LV_EVENT_GESTURE, NULL);
  lv_obj_add_event_cb(objects.app_camera, appSwipe, LV_EVENT_GESTURE, NULL);

  // Camera APP
  cam_img_dsc.header.always_zero = 0;
  cam_img_dsc.header.w = SCREEN_WIDTH;
  cam_img_dsc.header.h = SCREEN_HEIGHT;
  cam_img_dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
  cam_img_dsc.data_size = sizeof(cam_buf);
  cam_img_dsc.data = cam_buf;
}

void loop() {
  unsigned long now = millis();

  // Vibration
  updateVibration();

  // Read current RTC time
  rtc.getDate(&rtcDate);
  rtc.getTime(&rtcTime);

  // Keep track of millis offset inside the current second
  static unsigned long millisAtLastTick = 0;
  static int lastSecond = -1;
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
  lv_label_set_text_fmt(objects.battery_voltage, "%i%%", level);
  angle = map(level, 0, 100, -1200, 1200);
  lv_img_set_angle(objects.battery_hand, angle);
  lv_img_set_angle(objects.battery_hand_shadow, angle);


  // APPS
  if (activeApp == APP_CAMERA && !takingPhoto) {
    camera_fb_t *fb = esp_camera_fb_get();
    jpg2rgb565(fb->buf, fb->len, cam_buf, JPG_SCALE_NONE);
    esp_camera_fb_return(fb); // Return camera buffer

    // Update camera image in ui
    lv_img_set_src(objects.camera_feed, &cam_img_dsc);
    lv_obj_invalidate(objects.camera_feed);
  }

  // Update UI
  lv_timer_handler();
  ui_tick();

  // Auto sleep
  if (wakeUp) { // Turn on display after UI update
    digitalWrite(BACKLIGHT_PIN, HIGH); // Turn on display
    wakeUp = false;
  }

  if (digitalRead(TOUCH_INT_PIN) == LOW) lastActive = now;
  
  if (now - lastActive >= AUTO_SLEEP) {
    preferences.putBool("autoSleepFlag", true);
    ESP.restart();
  }
}

// VIBRATION
void vibrate(int duration = 10) {
  hapticStart = true;
  hapticDuration = duration;
}

void updateVibration() {
  if (hapticStart) {
    digitalWrite(HAPTIC_PIN, HIGH);
    hapticStart = false;
    hapticActive = true;
    hapticEnd = millis() + hapticDuration;
  }
  if (hapticActive && millis() >= hapticEnd) {
    digitalWrite(HAPTIC_PIN, LOW);
    hapticActive = false;
  }
}

// EVENT HANDLERS
void action_open_app_camera(lv_event_t *e) {
  initCam();
  loadScreenAnim(SCREEN_ID_APP_CAMERA, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 300);
  activeApp = APP_CAMERA;
}

void action_take_photo(lv_event_t *e) {
  unsigned long start = millis();
  takingPhoto = true;
  vibrate(20);

  sensor_t * s = esp_camera_sensor_get();
  s->set_framesize(s, FRAMESIZE_UXGA);

  // Throw away a couple of frames so exposure can settle
  for (int i = 0; i < 5; i++) {
    esp_camera_fb_return(esp_camera_fb_get());
  }

  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) return;

  rtc.getDate(&rtcDate);
  rtc.getTime(&rtcTime);

  char filename[32];
  snprintf(filename, sizeof(filename),
           "/%04d-%02d-%02d_%02d-%02d-%02d.jpg",
           rtcDate.year, rtcDate.month, rtcDate.date,
           rtcTime.hours, rtcTime.minutes, rtcTime.seconds);

  File file = SD.open(filename, FILE_WRITE);
  if (!file) return;
  
  file.write(fb->buf, fb->len);
  file.close();
  
  esp_camera_fb_return(fb);
  
  s->set_framesize(s, FRAMESIZE_240X240);
  Serial.printf("Took photo %s in %i ms\n", filename, (millis() - start));

  takingPhoto = false;
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

void watchfaceSwipe(lv_event_t * e) {
  lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
  if (dir == LV_DIR_LEFT) loadScreenAnim(SCREEN_ID_HOME, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300);
}

void homeSwipe(lv_event_t * e) {
  lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
  if (dir == LV_DIR_RIGHT) loadScreenAnim(SCREEN_ID_WATCHFACE, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300);
}

void appSwipe(lv_event_t * e) {
  lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
  if (dir == LV_DIR_TOP) {
    esp_camera_deinit();
    loadScreenAnim(SCREEN_ID_HOME, LV_SCR_LOAD_ANIM_MOVE_TOP, 300);
    activeApp = HOME;
  }
}