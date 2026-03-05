#define USE_TFT_ESPI_LIBRARY
#include "lv_xiao_round_screen.h"
#include <SPI.h>
#include <Wire.h>
#include <lvgl.h>
#include "I2C_BM8563.h"
#include "ui.h"
#include "actions.h"
#include "images.h"
#include "driver/gpio.h"
#include <esp_camera.h>
#include "SD.h"
#include <Preferences.h>
#include "camera.h"

#define sensor_t sensor_t_bmp
#include <Adafruit_Sensor.h>
#undef sensor_t

#include <Adafruit_BMP280.h>
#include <Adafruit_AHT10.h>

// APPS
enum AppID {
  WATCH_FACE,
  HOME,
  APP_CAMERA,
  APP_LASER,
  APP_WEATHER,
  APP_PHOTOS,
  APP_TIMER
};
AppID activeApp = WATCH_FACE;

// Camera app
uint8_t cam_buf[SCREEN_WIDTH * SCREEN_HEIGHT * 2];  // 2 bytes per pixel (RGB565)
static lv_img_dsc_t cam_img_dsc;

// Laser app
#define LASER_PIN 42
bool laserState = false;

// Timer app
bool activeTimer = false;
int timerHours = 0;
int timerMinutes = 0;
int timerSeconds = 0;
uint32_t timerDuration;
uint32_t timerStartEpoch;
uint32_t timerElapsedAtPause;
uint32_t timerElapsed;
float timerStartSecFraction;
float timerSecFractionAtPause;
bool timerPaused = false;
bool timerEnded = false;
uint32_t timerNextVibrationTime;

// Photos app
#define PHOTO_DIR "/img/"
#define PHOTO_LIST_FILE "/photos.txt"
#define PHOTO_LIST_FILE_TMP "/photos.tmp"  // used while deleting photo
#define MAX_PHOTOS 500
uint16_t photoCount = 0;
int currentPhoto = 0;
uint8_t photo_buf[200 * 150 * 2];  // 200x150 photo preview, 2 bytes per pixel (RGB565)
static lv_img_dsc_t photo_img_dsc;
bool loadFirstPhoto = false;
unsigned long firstPhotoLoadTime = 0;
bool showingDeletePhotoDialog = false;

// SD
#define SD_CS_PIN D2
#define FILENAME_LEN 32
char photoList[MAX_PHOTOS][FILENAME_LEN];

// Haptic
#define HAPTIC_PIN 41
void vibrateAsync(int duration);

// Display
#define BACKLIGHT_PIN D6
#define TOUCH_INT_PIN D7

// Haptic motor
unsigned long hapticEnd = 0;
int hapticDuration = 0;
bool hapticStart = false;
bool hapticActive = false;
void vibrate(int duration = 30) {
  digitalWrite(HAPTIC_PIN, HIGH);
  delay(duration);
  digitalWrite(HAPTIC_PIN, LOW);
}

// RTC
I2C_BM8563 rtc(I2C_BM8563_DEFAULT_ADDRESS, Wire);
I2C_BM8563_DateTypeDef rtcDate;
I2C_BM8563_TimeTypeDef rtcTime;
const char* days[] = {"Lun", "Mar", "Mer", "Jeu", "Ven", "Sam", "Dim"};
const char* months[] = {"janvier", "fevrier", "mars", "avril", "mai", "juin", "juillet", "aout", "septembre", "octobre", "novembre", "decembre"};
float secFraction;

// BMP280
#define SEA_LEVEL_HPA 1010.10
#define BMP_ADDRESS 0x77
Adafruit_BMP280 bmp;

// AHT20
Adafruit_AHT10 aht;

// BATTERY
#define NUM_ADC_SAMPLE 20           // Sampling frequency
#define BATTERY_DEFICIT_VOL 1400    // Battery voltage value at loss of charge (mV)
#define BATTERY_FULL_VOL 2030       // Battery voltage value at full charge (mV)

#define SECOND_ANGLE 3600.0 / 60.0
#define MINUTE_ANGLE 3600.0 / 60.0
#define HOUR_ANGLE   3600.0 / 12.0
#define MONTH_ANGLE  3600.0 / 12.0

// AUTO SLEEP
#define AUTO_SLEEP 20000  // Inactivity time for auto sleep (ms)
unsigned long lastActive = 0;
bool wakeUp = true;

// Preferences
Preferences preferences;

// Gesture control
bool startedGesture = false;
lv_coord_t touchX, touchY;
lv_coord_t gestureStartX;
lv_coord_t gestureStartY;
#define GESTURE_SIZE 30

void setup() {
  pinMode(TOUCH_INT_PIN, INPUT_PULLUP);
  pinMode(BACKLIGHT_PIN, OUTPUT);
  pinMode(LASER_PIN, OUTPUT);
  pinMode(HAPTIC_PIN, OUTPUT);

  digitalWrite(LASER_PIN, LOW);
  digitalWrite(HAPTIC_PIN, LOW);

  // Initialize display
  lv_init();
  lv_xiao_disp_init();
  lv_xiao_touch_init();
  ui_init();

  // Initialize SD card
  pinMode(SD_CS_PIN, OUTPUT);
  if (!SD.begin(SD_CS_PIN)) {
    Serial.begin(115200);
    Serial.println("Card mount failed. Check if watch is ON.");
    while (1) {}
  }

  // BMP280
  bmp.begin(BMP_ADDRESS);
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_1);   /* Standby time. */

  // AHT20
  aht.begin();

  preferences.begin("config", false);
  
  // Timer app
  if (preferences.getBool("activeTimer", false) && !preferences.getBool("timerEnded", true)) {  // If active timer
    activeTimer = true;
    timerEnded = preferences.getBool("timerEnded", true);
    timerDuration = preferences.getULong("tDuration", 0);
    timerStartEpoch = preferences.getULong("tStartEpoch", 0);
    timerElapsedAtPause = preferences.getULong("tElAtPause", 0);
    timerPaused = preferences.getBool("timerPaused", false);
    if (timerPaused) lv_obj_add_state(objects.timer_pause, LV_STATE_CHECKED);
  }

  // Auto sleep
  if (preferences.getBool("autoSleepFlag", false)) {
    preferences.putBool("autoSleepFlag", false);
    digitalWrite(BACKLIGHT_PIN, LOW);  // Turn off display backlight

    // Enable wakeup on touch pin, GPIO 44 (falling edge)
    gpio_wakeup_enable((gpio_num_t)TOUCH_INT_PIN, GPIO_INTR_LOW_LEVEL);
    esp_sleep_enable_gpio_wakeup();

    // Enable wakeup for timer
    if (activeTimer && !timerPaused) {
      // RTC
      Wire.begin();
      rtc.begin();

      uint32_t elapsed = getRtcEpoch() - timerStartEpoch;
      uint64_t wakeup_us = 0;

      if (elapsed >= timerDuration) {
          wakeup_us = 1000;  // wake up immediately (1ms)
      } else {
          uint32_t remaining = timerDuration - elapsed;
          wakeup_us = (uint64_t)remaining * 1000000ULL;
          if (wakeup_us < 1000) wakeup_us = 1000;
      }

      esp_sleep_enable_timer_wakeup(wakeup_us);
    }

    esp_light_sleep_start();  // ENTER LIGHT SLEEP

    lastActive = millis();
  } else {
    // First boot since powerup
    preferences.putBool("activeTimer", false);
  }
  
  Serial.begin(115200);

  // RTC
  Wire.begin();
  rtc.begin();

  // ADC
  analogReadResolution(12);

  // Camera APP
  cam_img_dsc.header.always_zero = 0;
  cam_img_dsc.header.w = SCREEN_WIDTH;
  cam_img_dsc.header.h = SCREEN_HEIGHT;
  cam_img_dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
  cam_img_dsc.data_size = sizeof(cam_buf);
  cam_img_dsc.data = cam_buf;

  // Photos APP
  photo_img_dsc.header.always_zero = 0;
  photo_img_dsc.header.w = 200;
  photo_img_dsc.header.h = 150;
  photo_img_dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
  photo_img_dsc.data_size = sizeof(photo_buf);
  photo_img_dsc.data = photo_buf;

  loadPhotoListFromSD();

  // Laser APP
  lv_obj_add_flag(objects.laser_icon_on, LV_OBJ_FLAG_HIDDEN);
}

void loop() {
  // Gesture control
  gestureTick();
  
  // Vibration
  vibrationTick();

  // Timer
  if (activeTimer) {
    if (timerPaused) timerElapsed = timerElapsedAtPause;
    else timerElapsed = getRtcEpoch() - timerStartEpoch;

    if (timerElapsed >= timerDuration && activeApp != APP_TIMER) {
      closeApp();
      activeApp = APP_TIMER;
    }
  }

  if (activeApp == WATCH_FACE || activeApp == HOME || activeApp == APP_TIMER) {
    // Read current RTC time
    rtc.getDate(&rtcDate);
    rtc.getTime(&rtcTime);

    // Keep track of millis offset inside the current second
    static unsigned long millisAtLastTick = 0;
    static int lastSecond = -1;
    if (rtcTime.seconds != lastSecond) {
      // New tick from RTC
      lastSecond = rtcTime.seconds;
      millisAtLastTick = millis();
    }
    secFraction = (millis() - millisAtLastTick) / 1000.0;
    if (secFraction > 1.0) secFraction = 1.0;
  }

  // APPS
  switch (activeApp) {
    case WATCH_FACE:
    case HOME: {
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

      // Temperature
      float temperature = bmp.readTemperature(); // *C
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
      break;
    }
    case APP_CAMERA: {
      camera_fb_t *fb = esp_camera_fb_get();
      jpg2rgb565(fb->buf, fb->len, cam_buf, JPG_SCALE_NONE);
      esp_camera_fb_return(fb);  // Return camera buffer

      // Update camera image in ui
      lv_img_set_src(objects.camera_feed, &cam_img_dsc);
      lv_obj_invalidate(objects.camera_feed);
      break;
    }
    case APP_WEATHER: {
      rtc.getDate(&rtcDate);
      rtc.getTime(&rtcTime);

      // Update background
      if (rtcTime.hours > 6 && rtcTime.hours < 18) {
        // DAY
        lv_obj_add_flag(objects.weather_app_bg_night, LV_OBJ_FLAG_HIDDEN);
      } else {
        // NIGHT
        lv_obj_clear_flag(objects.weather_app_bg_night, LV_OBJ_FLAG_HIDDEN);
      }

      // Update time and date labels
      lv_label_set_text_fmt(objects.time_weather, "%02i:%02i", rtcTime.hours, rtcTime.minutes);
      lv_label_set_text_fmt(objects.date_weather, "%s. %i %s", days[rtcDate.weekDay], rtcDate.date, months[rtcDate.month-1]);

      // AHT20
      sensors_event_t humidity, temp;
      aht.getEvent(&humidity, &temp);

      // Temperature
      char buf[7];
      sprintf(buf, "%.0f°C", temp.temperature);
      lv_label_set_text(objects.temperature_weather, buf);

      // Humidity
      sprintf(buf, "%.0f %%", humidity.relative_humidity);
      lv_label_set_text(objects.humidity, buf);

      // Altitude
      float altitude = bmp.readAltitude(SEA_LEVEL_HPA);  // m
      sprintf(buf, "%.0f m", altitude);
      lv_label_set_text(objects.altitude, buf);
      break;
    }
    case APP_PHOTOS: {
      if (loadFirstPhoto) {
        if (millis() > firstPhotoLoadTime) {
          currentPhoto = photoCount-1;
          while (photoCount && !loadPhoto(currentPhoto)) {
            currentPhoto = photoCount-1;
          }
          if (photoCount) lv_obj_clear_flag(objects.trash, LV_OBJ_FLAG_HIDDEN);
          loadFirstPhoto = false;
        }
        break;
      }

      static unsigned long lastTap = 0;
      if(!showingDeletePhotoDialog && chsc6x_read_touch(&touchX, &touchY) && millis()-lastTap >= 100) {
        if (touchX > 60 && touchX < SCREEN_WIDTH-60) break;
        
        if (touchX <= 60) {
          currentPhoto -= 1;
          if (currentPhoto < 0) currentPhoto = photoCount-1;
        } else {
          currentPhoto += 1;
          if (currentPhoto > photoCount-1) currentPhoto = 0;
        }
        vibrate();
        while (photoCount && !loadPhoto(currentPhoto)) {
          if (touchX <= 60) {
            currentPhoto -= 1;
            if (currentPhoto < 0) currentPhoto = photoCount-1;
          } else {
            // next photo has been pushed back to currentPhoto index
            if (currentPhoto > photoCount-1) currentPhoto = 0;
          }
        }
        lastTap = millis();
      }
      break;
    }
    case APP_TIMER: {
      if (activeTimer) {
        lv_obj_clear_flag(objects.active_timer_screen, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(objects.timer_set_screen, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(objects.timer_pause, LV_OBJ_FLAG_HIDDEN);
        
        if (timerElapsed >= timerDuration) {
          // Ended timer
          lv_arc_set_value(objects.timer_ring, 0);
          lv_obj_clear_flag(objects.timer_title_end, LV_OBJ_FLAG_HIDDEN);
          lv_obj_add_flag(objects.timer_pause, LV_OBJ_FLAG_HIDDEN);
          if (timerDuration < 3600) {
            lv_label_set_text(objects.timer_minutes_s, "00");
            lv_label_set_text(objects.timer_seconds_s, "00");
            lv_obj_clear_flag(objects.timer_s, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(objects.timer_l, LV_OBJ_FLAG_HIDDEN);
          } else {
            lv_label_set_text(objects.timer_hours_l, "00");
            lv_label_set_text(objects.timer_minutes_l, "00");
            lv_label_set_text(objects.timer_seconds_l, "00");
            lv_obj_clear_flag(objects.timer_l, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(objects.timer_s, LV_OBJ_FLAG_HIDDEN);
          }

          // Show timer screen if not on app
          if (!timerEnded) loadScreenAnim(SCREEN_ID_APP_TIMER, LV_SCR_LOAD_ANIM_NONE, 0);

          // ALARM
          if (!timerEnded || millis() > timerNextVibrationTime) {
            if (!timerEnded) {
              timerEnded = true;
              preferences.putBool("timerEnded", true);
            }
            vibrateAsync(300);
            timerNextVibrationTime = millis() + 600;
            lastActive = millis(); // don't go to sleep
          }
        } else {
          // Running timer
          lv_obj_add_flag(objects.timer_title_end, LV_OBJ_FLAG_HIDDEN);
          uint32_t remaining = timerDuration - timerElapsed;
          timerHours   = remaining / 3600;
          timerMinutes = (remaining % 3600) / 60;
          timerSeconds = remaining % 60;
          
          if (timerDuration < 3600) {
            // Less than 1h, show small timer (m:s)
            lv_label_set_text_fmt(objects.timer_minutes_s, "%02i", timerMinutes);
            lv_label_set_text_fmt(objects.timer_seconds_s, "%02i", timerSeconds);
            lv_obj_clear_flag(objects.timer_s, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(objects.timer_l, LV_OBJ_FLAG_HIDDEN);
          } else {
            // More than 1h, show large timer (h:m:s)
            lv_label_set_text_fmt(objects.timer_hours_l, "%02i", timerHours);
            lv_label_set_text_fmt(objects.timer_minutes_l, "%02i", timerMinutes);
            lv_label_set_text_fmt(objects.timer_seconds_l, "%02i", timerSeconds);
            lv_obj_clear_flag(objects.timer_l, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(objects.timer_s, LV_OBJ_FLAG_HIDDEN);
          }
          float remainingF;
          if (timerPaused) remainingF = (float)remaining - (timerSecFractionAtPause - timerStartSecFraction);
          else remainingF = (float)remaining - (secFraction - timerStartSecFraction);
          if (remainingF < 0.0f) remainingF = 0.0f;

          uint16_t ringDeg = (uint16_t)((remainingF * 360.0f) / timerDuration);
          lv_arc_set_value(objects.timer_ring, ringDeg);
        }
      } else {
        lv_obj_clear_flag(objects.timer_set_screen, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(objects.active_timer_screen, LV_OBJ_FLAG_HIDDEN);

        lv_label_set_text_fmt(objects.timer_set_hours, "%02i", timerHours);
        lv_label_set_text_fmt(objects.timer_set_minutes, "%02i", timerMinutes);
        lv_label_set_text_fmt(objects.timer_set_seconds, "%02i", timerSeconds);
        rtc.getTime(&rtcTime);
        lv_label_set_text_fmt(objects.time_timer_app, "%02i:%02i", rtcTime.hours, rtcTime.minutes);
      }
      break;
    }
  }

  // Update UI
  lv_timer_handler();
  ui_tick();

  // Auto sleep
  if (wakeUp) {  // Turn on display after UI update
    // Tick UI for frame to settle
    for(int i=0; i<4; i++) {
      lv_timer_handler();
      ui_tick();
    }
    digitalWrite(BACKLIGHT_PIN, HIGH);  // Turn on display
    wakeUp = false;
  }

  if (millis() - lastActive >= AUTO_SLEEP) {
    // Save timer before restart
    if (activeTimer) {
      saveTimerStateInNvs();
    } else {
      preferences.putBool("activeTimer", false);
    }

    preferences.putBool("autoSleepFlag", true);
    ESP.restart();
  }

  //Serial.printf("Free heap: %d bytes\n", ESP.getFreeHeap());
}

// UTILS
void vibrateAsync(int duration = 40) {
  hapticStart = true;
  hapticDuration = duration;
}

void vibrationTick() {
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

// Photos APP
bool scanDirForPhotos(const char *dirname) {
  // Scan SD
  File dir = SD.open(dirname);
  if (!dir) return false;

  photoCount = 0;
  File file;
  while ((file = dir.openNextFile()) && photoCount < MAX_PHOTOS) {
    if (file.isDirectory()) {
      file.close();
      continue;
    }
    const char *name = file.name();
    const char *ext = strrchr(name, '.');
    // Only .jpg / .JPG
    if (ext && strcasecmp(ext, ".jpg") == 0) {
      strncpy(photoList[photoCount], name, FILENAME_LEN - 1);
      photoList[photoCount][FILENAME_LEN - 1] = '\0';
      photoCount++;
    }
    file.close();
  }
  dir.close();

  // Sort photos by name
  for (uint16_t i = 0; i < photoCount - 1; i++) {
    for (uint16_t j = i + 1; j < photoCount; j++) {
      if (strcmp(photoList[i], photoList[j]) > 0) {
        char tmp[FILENAME_LEN];
        strcpy(tmp, photoList[i]);
        strcpy(photoList[i], photoList[j]);
        strcpy(photoList[j], tmp);
      }
    }
  }

  // Store list in txt file
  File f = SD.open(PHOTO_LIST_FILE, FILE_WRITE);
  if (!f) return false;

  for (int i = 0; i < photoCount; i++) {
    f.println(photoList[i]);
  }

  f.close();
  return true;
}

void loadPhotoListFromSD() {
  photoCount = 0;

  File f = SD.open(PHOTO_LIST_FILE, FILE_READ);
  if (!f) return;

  char line[FILENAME_LEN];
  while (f.available() && photoCount < MAX_PHOTOS) {
    size_t len = f.readBytesUntil('\n', line, FILENAME_LEN - 1);
    if (len == 0) continue;
    if (line[len - 1] == '\r') len--;  // Remove CR if file uses \r\n
    line[len] = '\0';

    strcpy(photoList[photoCount], line);
    photoCount++;
  }
  f.close();
}

bool removePhotoFromList(int idx) {
  File in = SD.open(PHOTO_LIST_FILE, FILE_READ);
  if (!in) return false;

  File out = SD.open(PHOTO_LIST_FILE_TMP, FILE_WRITE);
  if (!out) {
    in.close();
    return false;
  }

  char line[FILENAME_LEN];
  bool removed = false;

  while (in.available()) {
    size_t len = in.readBytesUntil('\n', line, sizeof(line) - 1);
    if (len == 0) continue;
    if (line[len - 1] == '\r') len--;  // Remove CR if file uses \r\n
    line[len] = '\0';

    if (strcmp(line, photoList[idx]) == 0) {
      removed = true;  // skip this line
    } else if (strlen(line) > 0) {
      out.println(line);
    }
  }

  in.close();
  out.close();

  SD.remove(PHOTO_LIST_FILE);
  SD.rename(PHOTO_LIST_FILE_TMP, PHOTO_LIST_FILE);

  for (int i = idx; i < photoCount - 1; i++) {
    strcpy(photoList[i], photoList[i + 1]);
  }
  photoCount--;

  return removed;
}

void appendPhotoToList(const char* filename) {
  File f = SD.open(PHOTO_LIST_FILE, FILE_APPEND);
  if (!f) return;
  f.println(filename);
  f.close();

  if (photoCount < MAX_PHOTOS) {
    strncpy(photoList[photoCount], filename, FILENAME_LEN-1); // skip '/'
    photoList[photoCount][FILENAME_LEN-1] = '\0';
    photoCount++;
  }
}

bool loadJpegFromSD(const char *path, uint32_t *outSize) {
  File file = SD.open(path, FILE_READ);
  if (!file) return false;

  uint32_t jpgSize = file.size();
  if (outSize) *outSize = jpgSize;

  uint8_t *jpgBuf = (uint8_t *)malloc(jpgSize);
  if (!jpgBuf) {
    file.close();
    return false;
  }

  file.read(jpgBuf, jpgSize);
  file.close();

  bool ok = jpg2rgb565(jpgBuf, jpgSize, photo_buf, JPG_SCALE_8X);

  free(jpgBuf);
  return ok;
}

bool loadPhoto(int index) {
  char path[FILENAME_LEN];
  snprintf(path, sizeof(path), "%s%s", PHOTO_DIR, photoList[index]);

  uint32_t photoSize;
  if (loadJpegFromSD(path, &photoSize)) {
    lv_img_set_src(objects.photo, &photo_img_dsc);
    lv_obj_invalidate(objects.photo);

    // Photo index
    lv_label_set_text_fmt(objects.photo_index, "%d / %d", index+1, photoCount);

    // Timestamp
    int year, month, day, hour, minute, second;
    if (sscanf(photoList[index], "%4d-%2d-%2d_%2d-%2d-%2d.jpg", &year, &month, &day, &hour, &minute, &second) == 6) {  // YYYY-MM-DD_HH-MM-SS.jpg
      lv_label_set_text_fmt(objects.photo_date, "%02d . %02d . %04d  %02d:%02d", day, month, year, hour, minute);
      lv_label_set_text_fmt(objects.photo_date_1, "%02d . %02d . %04d  %02d:%02d", day, month, year, hour, minute);
      lv_label_set_text_fmt(objects.photo_date_2, "%02d . %02d . %04d  %02d:%02d", day, month, year, hour, minute);
      lv_label_set_text_fmt(objects.photo_date_3, "%02d . %02d . %04d  %02d:%02d", day, month, year, hour, minute);
      lv_label_set_text_fmt(objects.photo_date_4, "%02d . %02d . %04d  %02d:%02d", day, month, year, hour, minute);
    } else {
      // Show filename
      //lv_label_set_text(objects.photo_date, photoList[index]);
    }

    // File size
    if (photoSize < 1024) {
      lv_label_set_text_fmt(objects.photo_size, "%lu B", photoSize);
    } else if (photoSize < 1024 * 1024) {
      lv_label_set_text_fmt(objects.photo_size, "%lu kB", photoSize / 1024);
    } else {
      lv_label_set_text_fmt(objects.photo_size, "%lu MB", photoSize / (1024*1024));
    }

    return true;
  }

  removePhotoFromList(index);
  return false;
}

// NAVIGATING MENUS
void closeApp() {
  switch (activeApp) {
    case APP_CAMERA: {
      esp_camera_deinit();
      break;
    }
    case APP_LASER: {
      digitalWrite(LASER_PIN, LOW);
      laserState = false;
      lv_obj_clear_state(objects.laser_toggle, LV_STATE_CHECKED);
      lv_obj_add_flag(objects.laser_icon_on, LV_OBJ_FLAG_HIDDEN);
      break;
    }
    case APP_TIMER: {
      if (activeTimer && timerEnded) {
        activeTimer = false;
        preferences.putBool("activeTimer", activeTimer);
        timerHours = 0;
        timerMinutes = 0;
        timerSeconds = 0;
        lv_label_set_text_fmt(objects.timer_set_hours, "%02i", timerHours);
        lv_label_set_text_fmt(objects.timer_set_minutes, "%02i", timerMinutes);
        lv_label_set_text_fmt(objects.timer_set_seconds, "%02i", timerSeconds);
        break;
      }
    }
  }
}

void gestureTick() {
  if (!chsc6x_read_touch(&touchX, &touchY)) {
    startedGesture = false;
    return;
  }
  if (touchX <= 1 || touchY <= 1) return;  // Ignore invalid coordinates

  lastActive = millis();

  if (!startedGesture) {
    // Start new gesture
    gestureStartX = touchX;
    gestureStartY = touchY;
    startedGesture = true;
    return;
  }

  lv_coord_t deltaX = touchX - gestureStartX;
  lv_coord_t deltaY = touchY - gestureStartY;
  if (abs(deltaX) < GESTURE_SIZE && abs(deltaY) < GESTURE_SIZE) return;

  // Horizontal gesture detected
  if (abs(deltaX) > abs(deltaY)) {
    if (deltaX < 0) {
      // LEFT
      if (activeApp == WATCH_FACE) {
        loadScreenAnim(SCREEN_ID_HOME, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300);
        activeApp = HOME;
      }
    } else {
      // RIGHT
      if (activeApp == HOME) {
        loadScreenAnim(SCREEN_ID_WATCHFACE, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300);
        activeApp = WATCH_FACE;
      }
    }
    // Vertical gesture detected
  } else {
    if (deltaY < 0) {
      // UP
      if (activeApp != WATCH_FACE && activeApp != HOME) {
        closeApp();
        loadScreenAnim(SCREEN_ID_HOME, LV_SCR_LOAD_ANIM_MOVE_TOP, 300);
        activeApp = HOME;
      }
    } else {
      // DOWN
    }
  }

  // Start new gesture
  gestureStartX = touchX;
  gestureStartY = touchY;
}

void action_open_app_camera(lv_event_t *e) {
  if (activeApp != HOME) return;
  initCam();
  loadScreenAnim(SCREEN_ID_APP_CAMERA, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 300);
  activeApp = APP_CAMERA;
}

void action_open_app_laser(lv_event_t *e) {
  if (activeApp != HOME) return;
  loadScreenAnim(SCREEN_ID_APP_LASER, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 300);
  activeApp = APP_LASER;
}

void action_open_app_weather(lv_event_t *e) {
  if (activeApp != HOME) return;
  loadScreenAnim(SCREEN_ID_APP_WEATHER, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 300);
  activeApp = APP_WEATHER;
}

void action_open_app_timer(lv_event_t *e) {
  if (activeApp != HOME) return;
  loadScreenAnim(SCREEN_ID_APP_TIMER, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 300);
  activeApp = APP_TIMER;

  if (!activeTimer) {
    timerHours = 0;
    timerMinutes = 0;
    timerSeconds = 0;
    lv_label_set_text_fmt(objects.timer_set_hours, "%02i", timerHours);
    lv_label_set_text_fmt(objects.timer_set_minutes, "%02i", timerMinutes);
    lv_label_set_text_fmt(objects.timer_set_seconds, "%02i", timerSeconds);
  }
}

void action_open_app_photos(lv_event_t *e) {
  if (activeApp != HOME) return;
  loadScreenAnim(SCREEN_ID_APP_PHOTOS, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 300);
  activeApp = APP_PHOTOS;

  lv_obj_add_flag(objects.confirm_delete_box, LV_OBJ_FLAG_HIDDEN);
  showingDeletePhotoDialog = false;

  lv_obj_add_flag(objects.trash, LV_OBJ_FLAG_HIDDEN);
  lv_img_set_src(objects.photo, &img_photo_loading);
  lv_label_set_text(objects.photo_size, "");
  lv_label_set_text(objects.photo_index, "");
  lv_label_set_text(objects.photo_date, "");
  lv_label_set_text(objects.photo_date_1, "");
  lv_label_set_text(objects.photo_date_2, "");
  lv_label_set_text(objects.photo_date_3, "");
  lv_label_set_text(objects.photo_date_4, "");
  loadFirstPhoto = true;
  firstPhotoLoadTime = millis()+350;
}

// EVENT HANDLERS: APPS
void action_toggle_laser(lv_event_t *e) {
  if (activeApp != APP_LASER) return;
  laserState = !laserState;
  if (laserState) {
    lv_obj_add_state(objects.laser_toggle, LV_STATE_CHECKED);
    lv_obj_clear_flag(objects.laser_icon_on, LV_OBJ_FLAG_HIDDEN);
  } else {
    lv_obj_clear_state(objects.laser_toggle, LV_STATE_CHECKED);
    lv_obj_add_flag(objects.laser_icon_on, LV_OBJ_FLAG_HIDDEN);
  }
  digitalWrite(LASER_PIN, laserState);
  vibrate();
}

// Timer app
void action_timer_hour_up(lv_event_t *e) {
  timerHours++;
  if (timerHours > 23) timerHours = 0;
  vibrate(18);
}

void action_timer_hour_down(lv_event_t *e) {
  timerHours--;
  if (timerHours < 0) timerHours = 23;
  vibrate(18);
}

void action_timer_minute_up(lv_event_t *e) {
  timerMinutes++;
  if (timerMinutes > 59) timerMinutes = 0;
  vibrate(18);
}

void action_timer_minute_down(lv_event_t *e) {
  timerMinutes--;
  if (timerMinutes < 0) timerMinutes = 59;
  vibrate(18);
}

void action_timer_second_up(lv_event_t *e) {
  timerSeconds++;
  if (timerSeconds > 59) timerSeconds = 0;
  vibrate(18);
}

void action_timer_second_down(lv_event_t *e) {
  timerSeconds--;
  if (timerSeconds < 0) timerSeconds = 59;
  vibrate(18);
}

void saveTimerStateInNvs() {
  preferences.putBool("activeTimer", activeTimer);
  preferences.putBool("timerEnded", timerEnded);
  preferences.putBool("timerPaused", timerPaused);
  preferences.putULong("tDuration", timerDuration);
  preferences.putULong("tStartEpoch", timerStartEpoch);
  preferences.putULong("tElAtPause", timerElapsedAtPause);
}

void action_timer_confirm(lv_event_t *e) {
  if (activeApp != APP_TIMER) return;

  // Start timer
  lv_obj_clear_state(objects.timer_pause, LV_STATE_CHECKED);

  timerDuration = timerHours * 3600 + timerMinutes * 60 + timerSeconds;
  if (!timerDuration) return;

  timerStartEpoch = getRtcEpoch();
  timerStartSecFraction = secFraction;
  timerPaused = false;
  timerEnded = false;
  activeTimer = true;
  saveTimerStateInNvs();

  vibrate();
}

void action_timer_restart(lv_event_t *e) {
  if (activeApp != APP_TIMER) return;

  // Restart timer
  lv_obj_clear_state(objects.timer_pause, LV_STATE_CHECKED);
  timerStartEpoch = getRtcEpoch();
  timerStartSecFraction = secFraction;
  timerPaused = false;
  timerEnded = false;
  activeTimer = true;
  saveTimerStateInNvs();

  vibrate();
}

void action_timer_pause(lv_event_t *e) {
  if (activeApp != APP_TIMER) return;

  timerPaused = !timerPaused;
  preferences.putBool("timerPaused", timerPaused);
  if (timerPaused) {
    // Pause
    timerElapsedAtPause = getRtcEpoch() - timerStartEpoch;
    preferences.putULong("tElAtPause", timerElapsedAtPause);
    timerSecFractionAtPause = secFraction;
    lv_obj_add_state(objects.timer_pause, LV_STATE_CHECKED);
  } else {
    // Unpause
    timerStartEpoch = getRtcEpoch() - timerElapsedAtPause;
    preferences.putULong("tStartEpoch", timerStartEpoch);
    lv_obj_clear_state(objects.timer_pause, LV_STATE_CHECKED);
  }
  vibrate();
}



void action_timer_cancel(lv_event_t *e) {
  if (activeApp != APP_TIMER) return;
  activeTimer = false;
  preferences.putBool("activeTimer", activeTimer);
  timerHours = 0;
  timerMinutes = 0;
  timerSeconds = 0;
  lv_label_set_text_fmt(objects.timer_set_hours, "%02i", timerHours);
  lv_label_set_text_fmt(objects.timer_set_minutes, "%02i", timerMinutes);
  lv_label_set_text_fmt(objects.timer_set_seconds, "%02i", timerSeconds);
  vibrate();
}

uint32_t getRtcEpoch() {
  rtc.getDate(&rtcDate);
  rtc.getTime(&rtcTime);

  struct tm t = {0};

  t.tm_year = rtcDate.year - 1900;
  t.tm_mon  = rtcDate.month - 1;
  t.tm_mday = rtcDate.date;
  t.tm_hour = rtcTime.hours;
  t.tm_min  = rtcTime.minutes;
  t.tm_sec  = rtcTime.seconds;
  t.tm_isdst = 0;

  time_t epoch = mktime(&t);

  // Anti glitch protection
  static uint32_t lastRtcEpoch = epoch;
  if (epoch < lastRtcEpoch) epoch = lastRtcEpoch; // glitch, ignore this epoch reading
  lastRtcEpoch = epoch;

  return epoch;
}

// Photo app
void action_take_photo(lv_event_t *e) {
  if (activeApp != APP_CAMERA) return;
  unsigned long start = millis();
  lastActive = start;
  vibrate();

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

  char filename[FILENAME_LEN];
  snprintf(filename, sizeof(filename),
           "%04d-%02d-%02d_%02d-%02d-%02d.jpg",
           rtcDate.year, rtcDate.month, rtcDate.date,
           rtcTime.hours, rtcTime.minutes, rtcTime.seconds); // YYYY-MM-DD_HH-MM-SS.jpg
  
  char filenameDir[FILENAME_LEN];
  snprintf(filenameDir, sizeof(filenameDir), "%s%s", PHOTO_DIR, filename);

  File file = SD.open(filenameDir, FILE_WRITE);
  if (!file) return;
  file.write(fb->buf, fb->len);
  file.close();

  esp_camera_fb_return(fb);
  s->set_framesize(s, FRAMESIZE_240X240);
  appendPhotoToList(filename);
  Serial.printf("Took photo %s in %i ms\n", filenameDir, (millis() - start));
  vibrate();
}

// Photos APP
void action_delete_photo(lv_event_t *e) {
  if (activeApp != APP_PHOTOS) return;
  if (showingDeletePhotoDialog) return;
  if (!photoCount) return;

  lv_label_set_text(objects.confirm_delete_filename, photoList[currentPhoto]);
  showingDeletePhotoDialog = true;
  lv_obj_clear_flag(objects.confirm_delete_box, LV_OBJ_FLAG_HIDDEN);
  vibrate();
}

void action_delete_photo_no(lv_event_t *e) {
  if (activeApp != APP_PHOTOS) return;

  showingDeletePhotoDialog = false;
  lv_obj_add_flag(objects.confirm_delete_box, LV_OBJ_FLAG_HIDDEN);
  vibrate();
}

void action_delete_photo_yes(lv_event_t *e) {
  if (activeApp != APP_PHOTOS) return;
  vibrate();

  char path[FILENAME_LEN];
  snprintf(path, sizeof(path), "%s%s", PHOTO_DIR, photoList[currentPhoto]);

  SD.remove(path);
  removePhotoFromList(currentPhoto);
  if (currentPhoto > 0) {
    currentPhoto -= 1;
  }

  while (photoCount && !loadPhoto(currentPhoto)) {
    if (currentPhoto > 0) {
      currentPhoto -= 1;
    }
  }

  if (!photoCount) {
    lv_img_set_src(objects.photo, &img_photo_loading);
    lv_label_set_text(objects.photo_size, "");
    lv_label_set_text(objects.photo_index, "");
    lv_label_set_text(objects.photo_date, "");
    lv_label_set_text(objects.photo_date_1, "");
    lv_label_set_text(objects.photo_date_2, "");
    lv_label_set_text(objects.photo_date_3, "");
    lv_label_set_text(objects.photo_date_4, "");
  }

  showingDeletePhotoDialog = false;
  lv_obj_add_flag(objects.confirm_delete_box, LV_OBJ_FLAG_HIDDEN);
}