#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

void create_screen_watchface() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.watchface = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SNAPPABLE|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    {
        lv_obj_t *parent_obj = obj;
        {
            // bg
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.bg = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_watchface);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
        }
        {
            // digital_time
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.digital_time = obj;
            lv_obj_set_pos(obj, 97, 68);
            lv_obj_set_size(obj, 46, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "12:34");
        }
        {
            // battery_voltage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.battery_voltage = obj;
            lv_obj_set_pos(obj, 158, 107);
            lv_obj_set_size(obj, 23, 12);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "90%");
        }
        {
            // temperature
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temperature = obj;
            lv_obj_set_pos(obj, 60, 107);
            lv_obj_set_size(obj, 23, 12);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "20°");
        }
        {
            // day_of_week
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.day_of_week = obj;
            lv_obj_set_pos(obj, 107, 161);
            lv_obj_set_size(obj, 25, 12);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Lun");
        }
        {
            // date
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.date = obj;
            lv_obj_set_pos(obj, 113, 175);
            lv_obj_set_size(obj, 15, 12);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "01");
        }
        {
            // month_marker
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.month_marker = obj;
            lv_obj_set_pos(obj, 115, 146);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_month_marker);
            lv_img_set_pivot(obj, 5, 26);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
        }
        {
            // temperature_hand
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.temperature_hand = obj;
            lv_obj_set_pos(obj, 68, 97);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_dial_hand);
            lv_img_set_pivot(obj, 3, 24);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
        }
        {
            // temperature_hand_shadow
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.temperature_hand_shadow = obj;
            lv_obj_set_pos(obj, 67, 100);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_dial_hand_shadow);
            lv_img_set_pivot(obj, 4, 25);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
        }
        {
            // battery_hand
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.battery_hand = obj;
            lv_obj_set_pos(obj, 165, 97);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_dial_hand);
            lv_img_set_pivot(obj, 3, 24);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
        }
        {
            // battery_hand_shadow
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.battery_hand_shadow = obj;
            lv_obj_set_pos(obj, 164, 100);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_dial_hand_shadow);
            lv_img_set_pivot(obj, 4, 25);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
        }
        {
            // hour_hand_shadow
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.hour_hand_shadow = obj;
            lv_obj_set_pos(obj, 113, 50);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_hour_hand_shadow);
            lv_img_set_pivot(obj, 7, 76);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
        }
        {
            // hour_hand
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.hour_hand = obj;
            lv_obj_set_pos(obj, 114, 44);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_hour_hand);
            lv_img_set_pivot(obj, 6, 76);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
        }
        {
            // minute_hand_shadow
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.minute_hand_shadow = obj;
            lv_obj_set_pos(obj, 114, 19);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_minute_hand_shadow);
            lv_img_set_pivot(obj, 6, 103);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
        }
        {
            // minute_hand
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.minute_hand = obj;
            lv_obj_set_pos(obj, 115, 13);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_minute_hand);
            lv_img_set_pivot(obj, 5, 106);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
        }
        {
            // second_hand_shadow
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.second_hand_shadow = obj;
            lv_obj_set_pos(obj, 115, 16);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_second_hand_shadow);
            lv_img_set_pivot(obj, 5, 110);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
        }
        {
            // second_hand
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.second_hand = obj;
            lv_obj_set_pos(obj, 116, 10);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_second_hand);
            lv_img_set_pivot(obj, 4, 110);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
        }
        {
            // top_bolt
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.top_bolt = obj;
            lv_obj_set_pos(obj, 116, 116);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_top_bolt);
        }
    }
    
    tick_screen_watchface();
}

void tick_screen_watchface() {
}

void create_screen_home() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.home = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SNAPPABLE|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_PRESSED);
    {
        lv_obj_t *parent_obj = obj;
        {
            // camera_app_icon
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.camera_app_icon = obj;
            lv_obj_set_pos(obj, 88, 88);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_cam_app_icon, NULL);
            lv_obj_add_event_cb(obj, action_open_app_camera, LV_EVENT_RELEASED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // laser_app_icon
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.laser_app_icon = obj;
            lv_obj_set_pos(obj, 126, 154);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_laser_app_icon, NULL);
            lv_obj_add_event_cb(obj, action_open_app_laser, LV_EVENT_RELEASED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // weather_app_icon
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.weather_app_icon = obj;
            lv_obj_set_pos(obj, 12, 88);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_weather_app_icon, NULL);
            lv_obj_add_event_cb(obj, action_open_app_weather, LV_EVENT_RELEASED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // photos_app_icon
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.photos_app_icon = obj;
            lv_obj_set_pos(obj, 164, 88);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_photos_app_icon, NULL);
            lv_obj_add_event_cb(obj, action_open_app_photos, LV_EVENT_RELEASED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // calculator_app_icon
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.calculator_app_icon = obj;
            lv_obj_set_pos(obj, 50, 22);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_calculator_app_icon, NULL);
            lv_obj_add_event_cb(obj, action_open_app_calc, LV_EVENT_RELEASED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // timer_app_icon
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.timer_app_icon = obj;
            lv_obj_set_pos(obj, 126, 22);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_timer_app_icon, NULL);
            lv_obj_add_event_cb(obj, action_open_app_timer, LV_EVENT_RELEASED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // settings_app_icon
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.settings_app_icon = obj;
            lv_obj_set_pos(obj, 50, 154);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_settings_app_icon, NULL);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
        }
    }
    
    tick_screen_home();
}

void tick_screen_home() {
}

void create_screen_app_camera() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.app_camera = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SNAPPABLE|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    {
        lv_obj_t *parent_obj = obj;
        {
            // camera_feed
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.camera_feed = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_camera);
        }
        {
            // shutter
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.shutter = obj;
            lv_obj_set_pos(obj, 93, 178);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 52);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_shutter, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_shutter_pressed, NULL);
            lv_obj_add_event_cb(obj, action_take_photo, LV_EVENT_RELEASED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
        }
    }
    
    tick_screen_app_camera();
}

void tick_screen_app_camera() {
}

void create_screen_app_laser() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.app_laser = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SNAPPABLE|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff151515), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 59, 42);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_laser_title);
        }
        {
            // laser_toggle
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.laser_toggle = obj;
            lv_obj_set_pos(obj, 28, 95);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 51);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_laser_toggle_off, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_laser_toggle_off, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &img_laser_toggle_on, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &img_laser_toggle_on, NULL);
            lv_obj_add_event_cb(obj, action_toggle_laser, LV_EVENT_RELEASED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // laser_icon_on
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.laser_icon_on = obj;
            lv_obj_set_pos(obj, 56, 166);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_laser_icon_on);
        }
        {
            // laser_icon_off
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.laser_icon_off = obj;
            lv_obj_set_pos(obj, 56, 166);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_laser_icon_off);
        }
    }
    
    tick_screen_app_laser();
}

void tick_screen_app_laser() {
}

void create_screen_app_weather() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.app_weather = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SNAPPABLE|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // weather_app_bg
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.weather_app_bg = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_weather_app_bg);
        }
        {
            // weather_app_bg_night
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.weather_app_bg_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_weather_app_bg_night);
        }
        {
            // temperature_weather
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temperature_weather = obj;
            lv_obj_set_pos(obj, 114, 93);
            lv_obj_set_size(obj, 68, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "20°C");
        }
        {
            // humidity
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.humidity = obj;
            lv_obj_set_pos(obj, 114, 141);
            lv_obj_set_size(obj, 86, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "14%");
        }
        {
            // altitude
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.altitude = obj;
            lv_obj_set_pos(obj, 114, 184);
            lv_obj_set_size(obj, 120, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "200 m");
        }
        {
            // time_weather
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.time_weather = obj;
            lv_obj_set_pos(obj, 98, 12);
            lv_obj_set_size(obj, 44, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "12:34");
        }
        {
            // date_weather
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.date_weather = obj;
            lv_obj_set_pos(obj, 30, 57);
            lv_obj_set_size(obj, 180, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Ven. 1 novembre");
        }
    }
    
    tick_screen_app_weather();
}

void tick_screen_app_weather() {
}

void create_screen_app_photos() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.app_photos = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SNAPPABLE|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // photo
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.photo = obj;
            lv_obj_set_pos(obj, 20, 45);
            lv_obj_set_size(obj, 200, 150);
            lv_img_set_src(obj, &img_photo_loading);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
        }
        {
            // right_arrow
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.right_arrow = obj;
            lv_obj_set_pos(obj, 225, 104);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_arrow_r);
        }
        {
            // left_arrow
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.left_arrow = obj;
            lv_obj_set_pos(obj, 3, 104);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_arrow_l);
        }
        {
            // trash
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.trash = obj;
            lv_obj_set_pos(obj, 111, 205);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_trash);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
        }
        {
            // delete_button
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.delete_button = obj;
            lv_obj_set_pos(obj, 95, 191);
            lv_obj_set_size(obj, 50, 50);
            lv_obj_add_event_cb(obj, action_delete_photo, LV_EVENT_RELEASED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // photo_index
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.photo_index = obj;
            lv_obj_set_pos(obj, 60, 24);
            lv_obj_set_size(obj, 120, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "12 / 34");
        }
        {
            // photo_size
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.photo_size = obj;
            lv_obj_set_pos(obj, 30, 4);
            lv_obj_set_size(obj, 180, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "100 kB");
        }
        {
            // photo_date_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.photo_date_1 = obj;
            lv_obj_set_pos(obj, 34, 172);
            lv_obj_set_size(obj, 180, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "15 . 01 . 2026  12:34");
        }
        {
            // photo_date_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.photo_date_2 = obj;
            lv_obj_set_pos(obj, 34, 174);
            lv_obj_set_size(obj, 180, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "15 . 01 . 2026  12:34");
        }
        {
            // photo_date_3
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.photo_date_3 = obj;
            lv_obj_set_pos(obj, 35, 173);
            lv_obj_set_size(obj, 180, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "15 . 01 . 2026  12:34");
        }
        {
            // photo_date_4
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.photo_date_4 = obj;
            lv_obj_set_pos(obj, 33, 173);
            lv_obj_set_size(obj, 180, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "15 . 01 . 2026  12:34");
        }
        {
            // photo_date
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.photo_date = obj;
            lv_obj_set_pos(obj, 34, 173);
            lv_obj_set_size(obj, 180, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffdc711a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "15 . 01 . 2026  12:34");
        }
        {
            // confirm_delete_box
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.confirm_delete_box = obj;
            lv_obj_set_pos(obj, 18, 59);
            lv_obj_set_size(obj, 205, 121);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // confirm_delete_filename
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.confirm_delete_filename = obj;
                    lv_obj_set_pos(obj, -6, -8);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff888888), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "2026-01-29_21_04_56.jpg");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj0 = obj;
                    lv_obj_set_pos(obj, -7, 13);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Supprimer la photo ?");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj1 = obj;
                    lv_obj_set_pos(obj, -7, 31);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Cette action est definitive");
                }
                {
                    // confirm_delete
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.confirm_delete = obj;
                    lv_obj_set_pos(obj, -7, 56);
                    lv_obj_set_size(obj, 78, 40);
                    lv_obj_add_event_cb(obj, action_delete_photo_no, LV_EVENT_RELEASED, (void *)0);
                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff7a7a7a), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Annuler");
                        }
                    }
                }
                {
                    // cancel_delete
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.cancel_delete = obj;
                    lv_obj_set_pos(obj, 75, 56);
                    lv_obj_set_size(obj, 109, 40);
                    lv_obj_add_event_cb(obj, action_delete_photo_yes, LV_EVENT_RELEASED, (void *)0);
                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff04d3d), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Supprimer");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_app_photos();
}

void tick_screen_app_photos() {
}

void create_screen_app_timer() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.app_timer = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SNAPPABLE|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // timer_set_screen
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.timer_set_screen = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // time_timer_app
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_timer_app = obj;
                    lv_obj_set_pos(obj, 98, 12);
                    lv_obj_set_size(obj, 44, 16);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "12:34");
                }
                {
                    // timer_title
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    objects.timer_title = obj;
                    lv_obj_set_pos(obj, 65, 32);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_img_set_src(obj, &img_timer_app_title);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                }
                {
                    // timer_set_hours
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.timer_set_hours = obj;
                    lv_obj_set_pos(obj, 23, 95);
                    lv_obj_set_size(obj, 56, 45);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00");
                }
                {
                    // timer_set_minutes
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.timer_set_minutes = obj;
                    lv_obj_set_pos(obj, 92, 95);
                    lv_obj_set_size(obj, 56, 45);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00");
                }
                {
                    // timer_set_seconds
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.timer_set_seconds = obj;
                    lv_obj_set_pos(obj, 161, 95);
                    lv_obj_set_size(obj, 56, 45);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00");
                }
                {
                    // h
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.h = obj;
                    lv_obj_set_pos(obj, 75, 112);
                    lv_obj_set_size(obj, 28, 16);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "h");
                }
                {
                    // m
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.m = obj;
                    lv_obj_set_pos(obj, 144, 113);
                    lv_obj_set_size(obj, 28, 16);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "m");
                }
                {
                    // s
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.s = obj;
                    lv_obj_set_pos(obj, 212, 112);
                    lv_obj_set_size(obj, 28, 16);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "s");
                }
                {
                    // arrow_d
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    objects.arrow_d = obj;
                    lv_obj_set_pos(obj, 35, 143);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_img_set_src(obj, &img_arrow_down);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                }
                {
                    // arrow_d_1
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    objects.arrow_d_1 = obj;
                    lv_obj_set_pos(obj, 104, 143);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_img_set_src(obj, &img_arrow_down);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                }
                {
                    // arrow_d_2
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    objects.arrow_d_2 = obj;
                    lv_obj_set_pos(obj, 173, 143);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_img_set_src(obj, &img_arrow_down);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                }
                {
                    // arrow_u
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    objects.arrow_u = obj;
                    lv_obj_set_pos(obj, 35, 72);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_img_set_src(obj, &img_arrow_up);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                }
                {
                    // arrow_u_1
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    objects.arrow_u_1 = obj;
                    lv_obj_set_pos(obj, 105, 72);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_img_set_src(obj, &img_arrow_up);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                }
                {
                    // arrow_u_2
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    objects.arrow_u_2 = obj;
                    lv_obj_set_pos(obj, 173, 72);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_img_set_src(obj, &img_arrow_up);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                }
                {
                    // hour_up_btn
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.hour_up_btn = obj;
                    lv_obj_set_pos(obj, 23, 39);
                    lv_obj_set_size(obj, 56, 68);
                    lv_obj_add_event_cb(obj, action_timer_hour_up, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_add_event_cb(obj, action_timer_hour_up, LV_EVENT_LONG_PRESSED_REPEAT, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // hour_down_btn
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.hour_down_btn = obj;
                    lv_obj_set_pos(obj, 23, 120);
                    lv_obj_set_size(obj, 56, 58);
                    lv_obj_add_event_cb(obj, action_timer_hour_down, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_add_event_cb(obj, action_timer_hour_down, LV_EVENT_LONG_PRESSED_REPEAT, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // minute_up_btn
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.minute_up_btn = obj;
                    lv_obj_set_pos(obj, 93, 39);
                    lv_obj_set_size(obj, 56, 68);
                    lv_obj_add_event_cb(obj, action_timer_minute_up, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_add_event_cb(obj, action_timer_minute_up, LV_EVENT_LONG_PRESSED_REPEAT, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // minute_down_btn
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.minute_down_btn = obj;
                    lv_obj_set_pos(obj, 93, 120);
                    lv_obj_set_size(obj, 56, 58);
                    lv_obj_add_event_cb(obj, action_timer_minute_down, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_add_event_cb(obj, action_timer_minute_down, LV_EVENT_LONG_PRESSED_REPEAT, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // second_down_btn
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.second_down_btn = obj;
                    lv_obj_set_pos(obj, 161, 120);
                    lv_obj_set_size(obj, 56, 58);
                    lv_obj_add_event_cb(obj, action_timer_second_down, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_add_event_cb(obj, action_timer_second_down, LV_EVENT_LONG_PRESSED_REPEAT, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // second_up_btn
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.second_up_btn = obj;
                    lv_obj_set_pos(obj, 161, 39);
                    lv_obj_set_size(obj, 56, 68);
                    lv_obj_add_event_cb(obj, action_timer_second_up, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_add_event_cb(obj, action_timer_second_up, LV_EVENT_LONG_PRESSED_REPEAT, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // timer_confirm
                    lv_obj_t *obj = lv_imgbtn_create(parent_obj);
                    objects.timer_confirm = obj;
                    lv_obj_set_pos(obj, 70, 188);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_timer_confirm, NULL);
                    lv_obj_add_event_cb(obj, action_timer_confirm, LV_EVENT_RELEASED, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_PRESSED);
                    lv_obj_set_style_img_recolor_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
                }
            }
        }
        {
            // active_timer_screen
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.active_timer_screen = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // timer_restart
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    objects.timer_restart = obj;
                    lv_obj_set_pos(obj, 61, 40);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_img_set_src(obj, &img_timer_restart);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                }
                {
                    // timer_restart_btn
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.timer_restart_btn = obj;
                    lv_obj_set_pos(obj, 60, 28);
                    lv_obj_set_size(obj, 56, 56);
                    lv_obj_add_event_cb(obj, action_timer_restart, LV_EVENT_RELEASED, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // timer_cancel
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    objects.timer_cancel = obj;
                    lv_obj_set_pos(obj, 124, 40);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_img_set_src(obj, &img_timer_cancel);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                }
                {
                    // timer_cancel_btn
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.timer_cancel_btn = obj;
                    lv_obj_set_pos(obj, 123, 28);
                    lv_obj_set_size(obj, 56, 56);
                    lv_obj_add_event_cb(obj, action_timer_cancel, LV_EVENT_RELEASED, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // timer_s
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.timer_s = obj;
                    lv_obj_set_pos(obj, 0, 92);
                    lv_obj_set_size(obj, 240, 56);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // timer_semicolon_s
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.timer_semicolon_s = obj;
                            lv_obj_set_pos(obj, 110, 6);
                            lv_obj_set_size(obj, 20, 45);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, ":");
                        }
                        {
                            // timer_minutes_s
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.timer_minutes_s = obj;
                            lv_obj_set_pos(obj, 59, 6);
                            lv_obj_set_size(obj, 56, 45);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "00");
                        }
                        {
                            // timer_seconds_s
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.timer_seconds_s = obj;
                            lv_obj_set_pos(obj, 125, 6);
                            lv_obj_set_size(obj, 56, 45);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "00");
                        }
                    }
                }
                {
                    // timer_l
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.timer_l = obj;
                    lv_obj_set_pos(obj, 0, 92);
                    lv_obj_set_size(obj, 240, 56);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // timer_hours_l
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.timer_hours_l = obj;
                            lv_obj_set_pos(obj, 31, 6);
                            lv_obj_set_size(obj, 56, 45);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "00");
                        }
                        {
                            // timer_semicolon_l
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.timer_semicolon_l = obj;
                            lv_obj_set_pos(obj, 82, 6);
                            lv_obj_set_size(obj, 20, 45);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, ":");
                        }
                        {
                            // timer_minutes_l
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.timer_minutes_l = obj;
                            lv_obj_set_pos(obj, 92, 6);
                            lv_obj_set_size(obj, 56, 45);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "00");
                        }
                        {
                            // timer_semicolon2_l
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.timer_semicolon2_l = obj;
                            lv_obj_set_pos(obj, 138, 6);
                            lv_obj_set_size(obj, 20, 45);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, ":");
                        }
                        {
                            // timer_seconds_l
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.timer_seconds_l = obj;
                            lv_obj_set_pos(obj, 153, 6);
                            lv_obj_set_size(obj, 56, 45);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "00");
                        }
                    }
                }
                {
                    // timer_pause
                    lv_obj_t *obj = lv_imgbtn_create(parent_obj);
                    objects.timer_pause = obj;
                    lv_obj_set_pos(obj, 97, 159);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, 46);
                    lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_timer_pause, NULL);
                    lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_timer_pause, NULL);
                    lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &img_timer_play, NULL);
                    lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &img_timer_play, NULL);
                    lv_obj_add_event_cb(obj, action_timer_pause, LV_EVENT_RELEASED, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_PRESSED);
                    lv_obj_set_style_img_recolor_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
                }
                {
                    // timer_title_end
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    objects.timer_title_end = obj;
                    lv_obj_set_pos(obj, 65, 165);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_img_set_src(obj, &img_timer_app_title);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                }
                {
                    // timerRing
                    lv_obj_t *obj = lv_arc_create(parent_obj);
                    objects.timer_ring = obj;
                    lv_obj_set_pos(obj, -1, -1);
                    lv_obj_set_size(obj, 242, 242);
                    lv_arc_set_range(obj, 0, 360);
                    lv_arc_set_value(obj, 300);
                    lv_arc_set_bg_start_angle(obj, 270);
                    lv_arc_set_bg_end_angle(obj, 269);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_set_style_arc_width(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(0xff444444), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                }
            }
        }
    }
    
    tick_screen_app_timer();
}

void tick_screen_app_timer() {
}

void create_screen_app_calc() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.app_calc = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SNAPPABLE|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // calc_result
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.calc_result = obj;
            lv_obj_set_pos(obj, 43, 20);
            lv_obj_set_size(obj, 118, 22);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "10 000 000");
        }
        {
            // backspace
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.backspace = obj;
            lv_obj_set_pos(obj, 166, 24);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_backspace);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
        }
        {
            // backspace_btn
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.backspace_btn = obj;
            lv_obj_set_pos(obj, 120, 0);
            lv_obj_set_size(obj, 120, 44);
            lv_obj_add_event_cb(obj, action_calc_backspace, LV_EVENT_RELEASED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // btn_clear
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_clear = obj;
            lv_obj_set_pos(obj, 37, 46);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_clear, NULL);
            lv_obj_add_event_cb(obj, action_calc_clear, LV_EVENT_RELEASED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_sign
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_sign = obj;
            lv_obj_set_pos(obj, 79, 46);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_sign, NULL);
            lv_obj_add_event_cb(obj, action_calc_sign, LV_EVENT_RELEASED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_mod
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_mod = obj;
            lv_obj_set_pos(obj, 121, 46);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_mod, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_btn_mod, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &img_btn_mod_active, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &img_btn_mod_active, NULL);
            lv_obj_add_event_cb(obj, action_calc_operation, LV_EVENT_RELEASED, (void *)4);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_divide
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_divide = obj;
            lv_obj_set_pos(obj, 163, 46);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_divide, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_btn_divide, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &img_btn_divide_active, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &img_btn_divide_active, NULL);
            lv_obj_add_event_cb(obj, action_calc_operation, LV_EVENT_RELEASED, (void *)3);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_x
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_x = obj;
            lv_obj_set_pos(obj, 163, 80);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_x, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_btn_x, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &img_btn_x_active, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &img_btn_x_active, NULL);
            lv_obj_add_event_cb(obj, action_calc_operation, LV_EVENT_RELEASED, (void *)2);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_minus
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_minus = obj;
            lv_obj_set_pos(obj, 163, 114);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn__, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_btn__, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &img_btn___active, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &img_btn___active, NULL);
            lv_obj_add_event_cb(obj, action_calc_operation, LV_EVENT_RELEASED, (void *)1);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_plus
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_plus = obj;
            lv_obj_set_pos(obj, 163, 148);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn__1, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_btn__1, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &img_btn___active1, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &img_btn___active1, NULL);
            lv_obj_add_event_cb(obj, action_calc_operation, LV_EVENT_RELEASED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_equal
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_equal = obj;
            lv_obj_set_pos(obj, 163, 182);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn__2, NULL);
            lv_obj_add_event_cb(obj, action_calc_equal, LV_EVENT_RELEASED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_7
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_7 = obj;
            lv_obj_set_pos(obj, 37, 80);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_7, NULL);
            lv_obj_add_event_cb(obj, action_calc_digit, LV_EVENT_RELEASED, (void *)7);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_8
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_8 = obj;
            lv_obj_set_pos(obj, 79, 80);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_8, NULL);
            lv_obj_add_event_cb(obj, action_calc_digit, LV_EVENT_RELEASED, (void *)8);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_9
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_9 = obj;
            lv_obj_set_pos(obj, 121, 80);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_9, NULL);
            lv_obj_add_event_cb(obj, action_calc_digit, LV_EVENT_RELEASED, (void *)9);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_4
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_4 = obj;
            lv_obj_set_pos(obj, 37, 114);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_4, NULL);
            lv_obj_add_event_cb(obj, action_calc_digit, LV_EVENT_RELEASED, (void *)4);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_5
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_5 = obj;
            lv_obj_set_pos(obj, 79, 114);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_5, NULL);
            lv_obj_add_event_cb(obj, action_calc_digit, LV_EVENT_RELEASED, (void *)5);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_6
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_6 = obj;
            lv_obj_set_pos(obj, 121, 114);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_6, NULL);
            lv_obj_add_event_cb(obj, action_calc_digit, LV_EVENT_RELEASED, (void *)6);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_1
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_1 = obj;
            lv_obj_set_pos(obj, 37, 148);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_1, NULL);
            lv_obj_add_event_cb(obj, action_calc_digit, LV_EVENT_RELEASED, (void *)1);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_2
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_2 = obj;
            lv_obj_set_pos(obj, 79, 148);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_2, NULL);
            lv_obj_add_event_cb(obj, action_calc_digit, LV_EVENT_RELEASED, (void *)2);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_3
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_3 = obj;
            lv_obj_set_pos(obj, 121, 148);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_3, NULL);
            lv_obj_add_event_cb(obj, action_calc_digit, LV_EVENT_RELEASED, (void *)3);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_0
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_0 = obj;
            lv_obj_set_pos(obj, 37, 182);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_0, NULL);
            lv_obj_add_event_cb(obj, action_calc_digit, LV_EVENT_RELEASED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // btn_comma
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.btn_comma = obj;
            lv_obj_set_pos(obj, 121, 182);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_comma, NULL);
            lv_obj_add_event_cb(obj, action_calc_comma, LV_EVENT_RELEASED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_img_recolor_opa(obj, 80, LV_PART_MAIN | LV_STATE_PRESSED);
        }
    }
    
    tick_screen_app_calc();
}

void tick_screen_app_calc() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_watchface,
    tick_screen_home,
    tick_screen_app_camera,
    tick_screen_app_laser,
    tick_screen_app_weather,
    tick_screen_app_photos,
    tick_screen_app_timer,
    tick_screen_app_calc,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_watchface();
    create_screen_home();
    create_screen_app_camera();
    create_screen_app_laser();
    create_screen_app_weather();
    create_screen_app_photos();
    create_screen_app_timer();
    create_screen_app_calc();
}
