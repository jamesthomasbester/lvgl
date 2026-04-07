#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include "../../lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_SCAN = 1,
    SCREEN_ID_HISTORY = 2,
    SCREEN_ID_SETTINGS = 3,
    SCREEN_ID_CALIBRATION = 4,
    SCREEN_ID_DISPLAY_COLOUR = 5,
    _SCREEN_ID_LAST = 5
};

typedef struct _objects_t {
    // Screens
    lv_obj_t *scan;
    lv_obj_t *history;
    lv_obj_t *settings;
    lv_obj_t *calibration;
    lv_obj_t *display_colour;

    // Scan screen
    lv_obj_t *scan_btn;
    lv_obj_t *scan_colour_preview;
    lv_obj_t *scan_hex_label;
    lv_obj_t *scan_rgb_label;

    // History screen
    lv_obj_t *history_table;

    // Settings screen
    lv_obj_t *settings_calibrate_btn;
    lv_obj_t *settings_wifi_btn;

    // Calibration screen
    lv_obj_t *cal_instruction_label;
    lv_obj_t *cal_scan_btn;
    lv_obj_t *cal_status_label;

    // Display colour screen
    lv_obj_t *colour_wheel;
    lv_obj_t *colour_preview;
    lv_obj_t *colour_hex_label;

    // Status bar (shared)
    lv_obj_t *status_wifi_label;
    lv_obj_t *status_battery_label;
    lv_obj_t *status_time_label;
} objects_t;

extern objects_t objects;

void create_screen_scan(void);
void tick_screen_scan(void);

void create_screen_history(void);
void tick_screen_history(void);

void create_screen_settings(void);
void tick_screen_settings(void);

void create_screen_calibration(void);
void tick_screen_calibration(void);

void create_screen_display_colour(void);
void tick_screen_display_colour(void);

void tick_screen(int screen_index);
void tick_screen_by_id(enum ScreensEnum screenId);

void create_screens(void);

// Status bar update helpers
void status_bar_set_battery(int percent);
void status_bar_set_wifi(bool connected);
void status_bar_set_time(const char *time_str);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/
