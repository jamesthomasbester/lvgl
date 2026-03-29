#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include "../../lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_SCAN = 2,
    SCREEN_ID_SETTINGS = 3,
    SCREEN_ID_HISTORY = 4,
    SCREEN_ID_DISPLAY_COLOUR = 5,
    SCREEN_ID_CALIBRATION_SCREEN = 6,
    _SCREEN_ID_LAST = 6
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *scan;
    lv_obj_t *settings;
    lv_obj_t *history;
    lv_obj_t *display_colour;
    lv_obj_t *calibration_screen;
    lv_obj_t *menu_scan_button;
    lv_obj_t *menu_history_button;
    lv_obj_t *menu_settings_button;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *red_label;
    lv_obj_t *green_label;
    lv_obj_t *blue_label;
    lv_obj_t *hex_label;
    lv_obj_t *red_value_label;
    lv_obj_t *green_value_label;
    lv_obj_t *blue_value_label;
    lv_obj_t *hex_value_label;
    lv_obj_t *obj3;
    lv_obj_t *menu_scan_button_1;
    lv_obj_t *menu_scan_button_2;
    lv_obj_t *obj4;
    lv_obj_t *history_list;
    lv_obj_t *obj5;
    lv_obj_t *colour_select_label;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void create_screen_scan();
void tick_screen_scan();

void create_screen_settings();
void tick_screen_settings();

void create_screen_history();
void tick_screen_history();

void create_screen_display_colour();
void tick_screen_display_colour();

void create_screen_calibration_screen();
void tick_screen_calibration_screen();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/