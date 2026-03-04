#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_camera;
extern const lv_img_dsc_t img_watchface;
extern const lv_img_dsc_t img_hour_hand;
extern const lv_img_dsc_t img_hour_hand_shadow;
extern const lv_img_dsc_t img_minute_hand;
extern const lv_img_dsc_t img_minute_hand_shadow;
extern const lv_img_dsc_t img_second_hand;
extern const lv_img_dsc_t img_second_hand_shadow;
extern const lv_img_dsc_t img_dial_hand;
extern const lv_img_dsc_t img_dial_hand_shadow;
extern const lv_img_dsc_t img_month_marker;
extern const lv_img_dsc_t img_top_bolt;
extern const lv_img_dsc_t img_cam_app_icon;
extern const lv_img_dsc_t img_shutter;
extern const lv_img_dsc_t img_shutter_pressed;
extern const lv_img_dsc_t img_laser_app_icon;
extern const lv_img_dsc_t img_no_app_icon;
extern const lv_img_dsc_t img_laser_toggle_on;
extern const lv_img_dsc_t img_laser_toggle_off;
extern const lv_img_dsc_t img_laser_icon_off;
extern const lv_img_dsc_t img_laser_icon_on;
extern const lv_img_dsc_t img_laser_title;
extern const lv_img_dsc_t img_weather_app_icon;
extern const lv_img_dsc_t img_calculator_app_icon;
extern const lv_img_dsc_t img_photos_app_icon;
extern const lv_img_dsc_t img_settings_app_icon;
extern const lv_img_dsc_t img_timer_app_icon;
extern const lv_img_dsc_t img_weather_app_bg;
extern const lv_img_dsc_t img_weather_app_bg_night;
extern const lv_img_dsc_t img_trash;
extern const lv_img_dsc_t img_arrow_r;
extern const lv_img_dsc_t img_arrow_l;
extern const lv_img_dsc_t img_photo_loading;
extern const lv_img_dsc_t img_arrow_down;
extern const lv_img_dsc_t img_arrow_up;
extern const lv_img_dsc_t img_timer_app_title;
extern const lv_img_dsc_t img_timer_cancel;
extern const lv_img_dsc_t img_timer_restart;
extern const lv_img_dsc_t img_timer_confirm;
extern const lv_img_dsc_t img_timer_pause;
extern const lv_img_dsc_t img_timer_play;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[41];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/