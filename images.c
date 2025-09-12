#include "images.h"

const ext_img_desc_t images[15] = {
    { "camera", &img_camera },
    { "watchface", &img_watchface },
    { "hour_hand", &img_hour_hand },
    { "hour_hand_shadow", &img_hour_hand_shadow },
    { "minute_hand", &img_minute_hand },
    { "minute_hand_shadow", &img_minute_hand_shadow },
    { "second_hand", &img_second_hand },
    { "second_hand_shadow", &img_second_hand_shadow },
    { "dial_hand", &img_dial_hand },
    { "dial_hand_shadow", &img_dial_hand_shadow },
    { "month_marker", &img_month_marker },
    { "top_bolt", &img_top_bolt },
    { "cam_app_icon", &img_cam_app_icon },
    { "shutter", &img_shutter },
    { "shutter_pressed", &img_shutter_pressed },
};
