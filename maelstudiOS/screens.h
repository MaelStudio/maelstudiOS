#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *watchface;
    lv_obj_t *home;
    lv_obj_t *app_camera;
    lv_obj_t *app_laser;
    lv_obj_t *app_weather;
    lv_obj_t *bg;
    lv_obj_t *digital_time;
    lv_obj_t *battery_voltage;
    lv_obj_t *temperature;
    lv_obj_t *day_of_week;
    lv_obj_t *date;
    lv_obj_t *month_marker;
    lv_obj_t *temperature_hand;
    lv_obj_t *temperature_hand_shadow;
    lv_obj_t *battery_hand;
    lv_obj_t *battery_hand_shadow;
    lv_obj_t *hour_hand_shadow;
    lv_obj_t *hour_hand;
    lv_obj_t *minute_hand_shadow;
    lv_obj_t *minute_hand;
    lv_obj_t *second_hand_shadow;
    lv_obj_t *second_hand;
    lv_obj_t *top_bolt;
    lv_obj_t *camera_app_icon;
    lv_obj_t *laser_app_icon;
    lv_obj_t *weather_app_icon;
    lv_obj_t *photos_app_icon;
    lv_obj_t *calculator_app_icon;
    lv_obj_t *timer_app_icon;
    lv_obj_t *settings_app_icon;
    lv_obj_t *camera_feed;
    lv_obj_t *shutter;
    lv_obj_t *laser_toggle;
    lv_obj_t *laser_icon_on;
    lv_obj_t *laser_icon_off;
    lv_obj_t *weather_app_bg;
    lv_obj_t *weather_app_bg_night;
    lv_obj_t *temperature_weather;
    lv_obj_t *humidity;
    lv_obj_t *altitude;
    lv_obj_t *time_weather;
    lv_obj_t *date_weather;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_WATCHFACE = 1,
    SCREEN_ID_HOME = 2,
    SCREEN_ID_APP_CAMERA = 3,
    SCREEN_ID_APP_LASER = 4,
    SCREEN_ID_APP_WEATHER = 5,
};

void create_screen_watchface();
void tick_screen_watchface();

void create_screen_home();
void tick_screen_home();

void create_screen_app_camera();
void tick_screen_app_camera();

void create_screen_app_laser();
void tick_screen_app_laser();

void create_screen_app_weather();
void tick_screen_app_weather();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/