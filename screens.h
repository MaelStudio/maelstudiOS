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
    lv_obj_t *camera_feed;
    lv_obj_t *shutter;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_WATCHFACE = 1,
    SCREEN_ID_HOME = 2,
    SCREEN_ID_APP_CAMERA = 3,
};

void create_screen_watchface();
void tick_screen_watchface();

void create_screen_home();
void tick_screen_home();

void create_screen_app_camera();
void tick_screen_app_camera();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/