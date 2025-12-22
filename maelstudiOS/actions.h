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


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/