#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_open_app_camera(lv_event_t * e);
extern void action_take_photo(lv_event_t * e);
extern void action_open_app_laser(lv_event_t * e);
extern void action_toggle_laser(lv_event_t * e);
extern void action_open_app_weather(lv_event_t * e);
extern void action_open_app_photos(lv_event_t * e);
extern void action_delete_photo(lv_event_t * e);
extern void action_delete_photo_yes(lv_event_t * e);
extern void action_delete_photo_no(lv_event_t * e);
extern void action_timer_confirm(lv_event_t * e);
extern void action_timer_hour_up(lv_event_t * e);
extern void action_timer_hour_down(lv_event_t * e);
extern void action_timer_minute_up(lv_event_t * e);
extern void action_timer_minute_down(lv_event_t * e);
extern void action_timer_second_up(lv_event_t * e);
extern void action_timer_second_down(lv_event_t * e);
extern void action_timer_restart(lv_event_t * e);
extern void action_timer_cancel(lv_event_t * e);
extern void action_timer_pause(lv_event_t * e);
extern void action_open_app_timer(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/