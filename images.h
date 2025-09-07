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

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[12];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/