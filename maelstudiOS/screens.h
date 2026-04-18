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
    lv_obj_t *app_photos;
    lv_obj_t *app_timer;
    lv_obj_t *app_calc;
    lv_obj_t *app_settings;
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
    lv_obj_t *photo;
    lv_obj_t *right_arrow;
    lv_obj_t *left_arrow;
    lv_obj_t *trash;
    lv_obj_t *delete_button;
    lv_obj_t *photo_index;
    lv_obj_t *photo_size;
    lv_obj_t *photo_date_1;
    lv_obj_t *photo_date_2;
    lv_obj_t *photo_date_3;
    lv_obj_t *photo_date_4;
    lv_obj_t *photo_date;
    lv_obj_t *confirm_delete_box;
    lv_obj_t *confirm_delete_filename;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *confirm_delete;
    lv_obj_t *cancel_delete;
    lv_obj_t *timer_set_screen;
    lv_obj_t *time_timer_app;
    lv_obj_t *timer_title;
    lv_obj_t *timer_set_hours;
    lv_obj_t *timer_set_minutes;
    lv_obj_t *timer_set_seconds;
    lv_obj_t *h;
    lv_obj_t *m;
    lv_obj_t *s;
    lv_obj_t *arrow_d;
    lv_obj_t *arrow_d_1;
    lv_obj_t *arrow_d_2;
    lv_obj_t *arrow_u;
    lv_obj_t *arrow_u_1;
    lv_obj_t *arrow_u_2;
    lv_obj_t *hour_up_btn;
    lv_obj_t *hour_down_btn;
    lv_obj_t *minute_up_btn;
    lv_obj_t *minute_down_btn;
    lv_obj_t *second_down_btn;
    lv_obj_t *second_up_btn;
    lv_obj_t *timer_confirm;
    lv_obj_t *active_timer_screen;
    lv_obj_t *timer_restart;
    lv_obj_t *timer_restart_btn;
    lv_obj_t *timer_cancel;
    lv_obj_t *timer_cancel_btn;
    lv_obj_t *timer_s;
    lv_obj_t *timer_semicolon_s;
    lv_obj_t *timer_minutes_s;
    lv_obj_t *timer_seconds_s;
    lv_obj_t *timer_l;
    lv_obj_t *timer_hours_l;
    lv_obj_t *timer_semicolon_l;
    lv_obj_t *timer_minutes_l;
    lv_obj_t *timer_semicolon2_l;
    lv_obj_t *timer_seconds_l;
    lv_obj_t *timer_pause;
    lv_obj_t *timer_title_end;
    lv_obj_t *timer_ring;
    lv_obj_t *calc_result;
    lv_obj_t *backspace;
    lv_obj_t *backspace_btn;
    lv_obj_t *btn_clear;
    lv_obj_t *btn_sign;
    lv_obj_t *btn_mod;
    lv_obj_t *btn_divide;
    lv_obj_t *btn_x;
    lv_obj_t *btn_minus;
    lv_obj_t *btn_plus;
    lv_obj_t *btn_equal;
    lv_obj_t *btn_7;
    lv_obj_t *btn_8;
    lv_obj_t *btn_9;
    lv_obj_t *btn_4;
    lv_obj_t *btn_5;
    lv_obj_t *btn_6;
    lv_obj_t *btn_1;
    lv_obj_t *btn_2;
    lv_obj_t *btn_3;
    lv_obj_t *btn_0;
    lv_obj_t *btn_comma;
    lv_obj_t *settings_pressure_plus;
    lv_obj_t *settings_month_plus;
    lv_obj_t *settings_date_plus;
    lv_obj_t *settings_day_plus;
    lv_obj_t *settings_time_plus;
    lv_obj_t *settings_title;
    lv_obj_t *settings_time;
    lv_obj_t *settings_day;
    lv_obj_t *settings_date;
    lv_obj_t *settings_month;
    lv_obj_t *settings_pressure;
    lv_obj_t *left_arrow_1;
    lv_obj_t *right_arrow_1;
    lv_obj_t *right_arrow_2;
    lv_obj_t *left_arrow_2;
    lv_obj_t *right_arrow_3;
    lv_obj_t *left_arrow_3;
    lv_obj_t *right_arrow_4;
    lv_obj_t *left_arrow_4;
    lv_obj_t *right_arrow_5;
    lv_obj_t *left_arrow_5;
    lv_obj_t *settings_pressure_minus;
    lv_obj_t *settings_month_minus;
    lv_obj_t *settings_date_minus;
    lv_obj_t *settings_day_minus;
    lv_obj_t *settings_time_minus;
    lv_obj_t *settings_save;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_WATCHFACE = 1,
    SCREEN_ID_HOME = 2,
    SCREEN_ID_APP_CAMERA = 3,
    SCREEN_ID_APP_LASER = 4,
    SCREEN_ID_APP_WEATHER = 5,
    SCREEN_ID_APP_PHOTOS = 6,
    SCREEN_ID_APP_TIMER = 7,
    SCREEN_ID_APP_CALC = 8,
    SCREEN_ID_APP_SETTINGS = 9,
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

void create_screen_app_photos();
void tick_screen_app_photos();

void create_screen_app_timer();
void tick_screen_app_timer();

void create_screen_app_calc();
void tick_screen_app_calc();

void create_screen_app_settings();
void tick_screen_app_settings();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/