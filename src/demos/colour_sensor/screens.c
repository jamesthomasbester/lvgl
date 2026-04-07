#include <string.h>
#include <stdlib.h>
#include "screens.h"
#include "styles.h"
#include "actions.h"
#include "vars.h"
#include "ui.h"

objects_t objects;

lv_obj_t *tick_value_change_obj;

// ─── Helpers ────────────────────────────────────────────────────────────────

static lv_obj_t *create_screen_base(void) {
    lv_obj_t *scr = lv_obj_create(NULL);
    lv_obj_add_style(scr, &style_screen, 0);
    lv_obj_set_size(scr, 240, 240);
    lv_obj_set_scrollbar_mode(scr, LV_SCROLLBAR_MODE_OFF);
    return scr;
}

// Accent left-border divider (red vertical bar like the portfolio cards)
static void add_accent_bar(lv_obj_t *parent, int x, int y, int h) {
    lv_obj_t *bar = lv_obj_create(parent);
    lv_obj_add_style(bar, &style_divider, 0);
    lv_obj_set_pos(bar, x, y);
    lv_obj_set_size(bar, 2, h);
}

static lv_obj_t *create_status_bar(lv_obj_t *parent) {
    lv_obj_t *bar = lv_obj_create(parent);
    lv_obj_add_style(bar, &style_status_bar, 0);
    lv_obj_set_pos(bar, 0, 0);
    lv_obj_set_size(bar, 240, 22);
    lv_obj_set_scrollbar_mode(bar, LV_SCROLLBAR_MODE_OFF);

    objects.status_time_label = lv_label_create(bar);
    lv_obj_add_style(objects.status_time_label, &style_label_grey, 0);
    lv_obj_align(objects.status_time_label, LV_ALIGN_LEFT_MID, 65, 0);
    lv_label_set_text(objects.status_time_label, "00:00");

    objects.status_wifi_label = lv_label_create(bar);
    lv_obj_add_style(objects.status_wifi_label, &style_label_grey, 0);
    lv_obj_align(objects.status_wifi_label, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(objects.status_wifi_label, LV_SYMBOL_WIFI);

    objects.status_battery_label = lv_label_create(bar);
    lv_obj_add_style(objects.status_battery_label, &style_label_grey, 0);
    lv_obj_align(objects.status_battery_label, LV_ALIGN_RIGHT_MID, -65, 0);
    lv_label_set_text(objects.status_battery_label, "100%");

    return bar;
}

static lv_obj_t *create_nav_btn(lv_obj_t *parent, const char *label, lv_event_cb_t cb, int x) {
    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_add_style(btn, &style_ghost_btn, 0);
    lv_obj_set_pos(btn, x, 205);
    lv_obj_set_size(btn, 26, 26);
    lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *lbl = lv_label_create(btn);
    lv_obj_add_style(lbl, &style_label_grey, 0);
    lv_label_set_text(lbl, label);
    lv_obj_center(lbl);
    return btn;
}

// ─── Nav callbacks ──────────────────────────────────────────────────────────

static void nav_to_scan(lv_event_t *e)         { lv_scr_load(objects.scan); }
static void nav_to_history(lv_event_t *e)      { lv_scr_load(objects.history); }
static void nav_to_settings(lv_event_t *e)     { lv_scr_load(objects.settings); }
static void nav_to_calibration(lv_event_t *e)  { lv_scr_load(objects.calibration); }
static void nav_to_display_colour(lv_event_t *e) { lv_scr_load(objects.display_colour); }

static void add_nav_bar(lv_obj_t *parent) {
    lv_obj_t *line = lv_obj_create(parent);
    lv_obj_add_style(line, &style_divider, 0);
    lv_obj_set_pos(line, 50, 203);
    lv_obj_set_size(line, 140, 1);

    // 5 buttons x 30px + 4 gaps x 5px = 170px, centered: start = (240-170)/2 = 35
    create_nav_btn(parent, LV_SYMBOL_HOME,     nav_to_scan,           55);
    create_nav_btn(parent, LV_SYMBOL_LIST,     nav_to_history,        80);
    create_nav_btn(parent, LV_SYMBOL_SETTINGS, nav_to_settings,      105);
    create_nav_btn(parent, LV_SYMBOL_EDIT,     nav_to_calibration,   130);
    create_nav_btn(parent, LV_SYMBOL_EYE_OPEN, nav_to_display_colour,155);
}

// ─── Scan Screen ────────────────────────────────────────────────────────────

static void scan_btn_cb(lv_event_t *e) { action_scan_colour(e); }

void create_screen_scan(void) {
    lv_obj_t *scr = create_screen_base();
    objects.scan = scr;

    create_status_bar(scr);

    // Title
    add_accent_bar(scr, 35, 27, 14);
    lv_obj_t *title = lv_label_create(scr);
    lv_obj_add_style(title, &style_label_title, 0);
    lv_obj_set_pos(title, 43, 26);
    lv_label_set_text(title, "SCAN");

    // Colour preview box - centered, inset from edges
    objects.scan_colour_preview = lv_obj_create(scr);
    lv_obj_add_style(objects.scan_colour_preview, &style_surface, 0);
    lv_obj_set_pos(objects.scan_colour_preview, 35, 48);
    lv_obj_set_size(objects.scan_colour_preview, 170, 70);
    lv_obj_set_scrollbar_mode(objects.scan_colour_preview, LV_SCROLLBAR_MODE_OFF);

    objects.scan_hex_label = lv_label_create(objects.scan_colour_preview);
    lv_obj_add_style(objects.scan_hex_label, &style_label_body, 0);
    lv_obj_align(objects.scan_hex_label, LV_ALIGN_CENTER, 0, -8);
    lv_label_set_text(objects.scan_hex_label, "#------");

    objects.scan_rgb_label = lv_label_create(objects.scan_colour_preview);
    lv_obj_add_style(objects.scan_rgb_label, &style_label_grey, 0);
    lv_obj_align(objects.scan_rgb_label, LV_ALIGN_CENTER, 0, 10);
    lv_label_set_text(objects.scan_rgb_label, "R:-- G:-- B:--");

    // Accent label
    lv_obj_t *sub = lv_label_create(scr);
    lv_obj_add_style(sub, &style_label_accent, 0);
    lv_obj_set_pos(sub, 35, 126);
    lv_label_set_text(sub, "TOUCH TO SCAN:");

    // Scan button - centered
    objects.scan_btn = lv_btn_create(scr);
    lv_obj_add_style(objects.scan_btn, &style_accent_btn, 0);
    lv_obj_set_pos(objects.scan_btn, 35, 138);
    lv_obj_set_size(objects.scan_btn, 170, 40);
    lv_obj_add_event_cb(objects.scan_btn, scan_btn_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *scan_lbl = lv_label_create(objects.scan_btn);
    lv_obj_add_style(scan_lbl, &style_label_body, 0);
    lv_label_set_text(scan_lbl, LV_SYMBOL_REFRESH "  SCAN COLOUR");
    lv_obj_center(scan_lbl);

    add_nav_bar(scr);
    tick_screen_scan();
}

void tick_screen_scan(void) {
    const char *hex = get_var_hex_value();
    const char *cur_hex = lv_label_get_text(objects.scan_hex_label);
    if (strcmp(hex, cur_hex) != 0) {
        lv_label_set_text(objects.scan_hex_label, hex);
        uint32_t colour = (uint32_t)strtol(hex + 1, NULL, 16);
        lv_obj_set_style_bg_color(objects.scan_colour_preview, lv_color_hex(colour), 0);
        lv_obj_set_style_bg_opa(objects.scan_colour_preview, LV_OPA_COVER, 0);
    }
}

// ─── History Screen ──────────────────────────────────────────────────────────

void create_screen_history(void) {
    lv_obj_t *scr = create_screen_base();
    objects.history = scr;
    create_status_bar(scr);
    add_accent_bar(scr, 35, 27, 14);
    lv_obj_t *title = lv_label_create(scr);
    lv_obj_add_style(title, &style_label_title, 0);
    lv_obj_set_pos(title, 43, 26);
    lv_label_set_text(title, "HISTORY");
    objects.history_table = lv_table_create(scr);
    lv_obj_add_style(objects.history_table, &style_table, 0);
    lv_obj_add_style(objects.history_table, &style_table, LV_PART_ITEMS);
    lv_obj_set_pos(objects.history_table, 35, 48);
    lv_obj_set_size(objects.history_table, 170, 150);
    lv_obj_set_scrollbar_mode(objects.history_table, LV_SCROLLBAR_MODE_OFF);
    lv_table_set_col_cnt(objects.history_table, 2);
    lv_table_set_col_width(objects.history_table, 0, 110);
    lv_table_set_col_width(objects.history_table, 1, 86);
    lv_table_set_cell_value(objects.history_table, 0, 0, "HEX");
    lv_table_set_cell_value(objects.history_table, 0, 1, "TIME");
    add_nav_bar(scr);
    tick_screen_history();
}

void tick_screen_history(void) {
    for (int i = 0; i < 8; i++) {
        const char *val = get_var_history_value(i);
        lv_table_set_cell_value(objects.history_table, i + 1, 0, val);
        lv_table_set_cell_value(objects.history_table, i + 1, 1, "--:--");
    }
}

// ─── Settings Screen ─────────────────────────────────────────────────────────

void create_screen_settings(void) {
    lv_obj_t *scr = create_screen_base();
    objects.settings = scr;
    create_status_bar(scr);
    add_accent_bar(scr, 35, 27, 14);
    lv_obj_t *title = lv_label_create(scr);
    lv_obj_add_style(title, &style_label_title, 0);
    lv_obj_set_pos(title, 43, 26);
    lv_label_set_text(title, "SETTINGS");

    lv_obj_t *cal_label = lv_label_create(scr);
    lv_obj_add_style(cal_label, &style_label_accent, 0);
    lv_obj_set_pos(cal_label, 35, 50);
    lv_label_set_text(cal_label, "SENSOR:");

    objects.settings_calibrate_btn = lv_btn_create(scr);
    lv_obj_add_style(objects.settings_calibrate_btn, &style_ghost_btn, 0);
    lv_obj_set_pos(objects.settings_calibrate_btn, 35, 62);
    lv_obj_set_size(objects.settings_calibrate_btn, 170, 36);
    lv_obj_add_event_cb(objects.settings_calibrate_btn, nav_to_calibration, LV_EVENT_CLICKED, NULL);
    lv_obj_t *cal_btn_lbl = lv_label_create(objects.settings_calibrate_btn);
    lv_obj_add_style(cal_btn_lbl, &style_label_body, 0);
    lv_label_set_text(cal_btn_lbl, "Calibrate  " LV_SYMBOL_RIGHT);
    lv_obj_center(cal_btn_lbl);

    lv_obj_t *div = lv_obj_create(scr);
    lv_obj_add_style(div, &style_divider, 0);
    lv_obj_set_pos(div, 35, 106);
    lv_obj_set_size(div, 170, 1);

    lv_obj_t *wifi_label = lv_label_create(scr);
    lv_obj_add_style(wifi_label, &style_label_accent, 0);
    lv_obj_set_pos(wifi_label, 35, 114);
    lv_label_set_text(wifi_label, "CONNECTIVITY:");

    objects.settings_wifi_btn = lv_btn_create(scr);
    lv_obj_add_style(objects.settings_wifi_btn, &style_ghost_btn, 0);
    lv_obj_set_pos(objects.settings_wifi_btn, 35, 126);
    lv_obj_set_size(objects.settings_wifi_btn, 170, 36);
    lv_obj_t *wifi_btn_lbl = lv_label_create(objects.settings_wifi_btn);
    lv_obj_add_style(wifi_btn_lbl, &style_label_body, 0);
    lv_label_set_text(wifi_btn_lbl, LV_SYMBOL_WIFI "  WiFi  " LV_SYMBOL_RIGHT);
    lv_obj_center(wifi_btn_lbl);

    add_nav_bar(scr);
    tick_screen_settings();
}

void tick_screen_settings(void) {}

// ─── Calibration Screen ──────────────────────────────────────────────────────

static void cal_scan_cb(lv_event_t *e) { action_scan_colour(e); }

void create_screen_calibration(void) {
    lv_obj_t *scr = create_screen_base();
    objects.calibration = scr;
    create_status_bar(scr);
    add_accent_bar(scr, 35, 27, 14);
    lv_obj_t *title = lv_label_create(scr);
    lv_obj_add_style(title, &style_label_title, 0);
    lv_obj_set_pos(title, 43, 26);
    lv_label_set_text(title, "CALIBRATE");

    objects.cal_status_label = lv_label_create(scr);
    lv_obj_add_style(objects.cal_status_label, &style_label_accent, 0);
    lv_obj_set_pos(objects.cal_status_label, 35, 50);
    lv_label_set_text(objects.cal_status_label, "STEP 1 OF 2:");

    lv_obj_t *card = lv_obj_create(scr);
    lv_obj_add_style(card, &style_surface, 0);
    lv_obj_set_pos(card, 35, 62);
    lv_obj_set_size(card, 170, 56);
    lv_obj_set_scrollbar_mode(card, LV_SCROLLBAR_MODE_OFF);

    objects.cal_instruction_label = lv_label_create(card);
    lv_obj_add_style(objects.cal_instruction_label, &style_label_body, 0);
    lv_label_set_long_mode(objects.cal_instruction_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(objects.cal_instruction_label, 184);
    lv_obj_align(objects.cal_instruction_label, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_label_set_text(objects.cal_instruction_label, "Point at PURE WHITE and scan.");

    objects.cal_scan_btn = lv_btn_create(scr);
    lv_obj_add_style(objects.cal_scan_btn, &style_accent_btn, 0);
    lv_obj_set_pos(objects.cal_scan_btn, 35, 128);
    lv_obj_set_size(objects.cal_scan_btn, 170, 40);
    lv_obj_add_event_cb(objects.cal_scan_btn, cal_scan_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *cal_lbl = lv_label_create(objects.cal_scan_btn);
    lv_obj_add_style(cal_lbl, &style_label_body, 0);
    lv_label_set_text(cal_lbl, LV_SYMBOL_REFRESH "  SCAN");
    lv_obj_center(cal_lbl);

    add_nav_bar(scr);
    tick_screen_calibration();
}

void tick_screen_calibration(void) {}

// ─── Display Colour Screen ───────────────────────────────────────────────────

static void colorwheel_cb(lv_event_t *e) {
    lv_obj_t *cw = lv_event_get_target(e);
    lv_color_t col = lv_colorwheel_get_rgb(cw);
    lv_obj_set_style_bg_color(objects.colour_preview, col, 0);
    static char hex_buf[8];
    snprintf(hex_buf, sizeof(hex_buf), "#%02X%02X%02X", col.ch.red << 3, col.ch.green << 2, col.ch.blue << 3);
    lv_label_set_text(objects.colour_hex_label, hex_buf);
}

void create_screen_display_colour(void) {
    lv_obj_t *scr = create_screen_base();
    objects.display_colour = scr;
    create_status_bar(scr);
    add_accent_bar(scr, 35, 27, 14);
    lv_obj_t *title = lv_label_create(scr);
    lv_obj_add_style(title, &style_label_title, 0);
    lv_obj_set_pos(title, 43, 26);
    lv_label_set_text(title, "COLOUR");

    // Colour wheel - centered
    objects.colour_wheel = lv_colorwheel_create(scr, true);
    lv_obj_set_pos(objects.colour_wheel, 20, 46);
    lv_obj_set_size(objects.colour_wheel, 110, 110);
    lv_obj_add_event_cb(objects.colour_wheel, colorwheel_cb, LV_EVENT_VALUE_CHANGED, NULL);

    // Colour preview box
    objects.colour_preview = lv_obj_create(scr);
    lv_obj_add_style(objects.colour_preview, &style_surface, 0);
    lv_obj_set_pos(objects.colour_preview, 140, 46);
    lv_obj_set_size(objects.colour_preview, 80, 80);
    lv_obj_set_scrollbar_mode(objects.colour_preview, LV_SCROLLBAR_MODE_OFF);

    objects.colour_hex_label = lv_label_create(scr);
    lv_obj_add_style(objects.colour_hex_label, &style_label_grey, 0);
    lv_obj_set_pos(objects.colour_hex_label, 140, 130);
    lv_label_set_text(objects.colour_hex_label, "#000000");

    lv_obj_t *info = lv_label_create(scr);
    lv_obj_add_style(info, &style_label_accent, 0);
    lv_obj_set_pos(info, 25, 165);
    lv_label_set_long_mode(info, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(info, 190);
    lv_label_set_text(info, "Display colour may differ from real life.");

    add_nav_bar(scr);
    tick_screen_display_colour();
}

void tick_screen_display_colour(void) {}

// ─── Status bar helpers ──────────────────────────────────────────────────────

void status_bar_set_battery(int percent) {
    static char buf[8];
    snprintf(buf, sizeof(buf), "%d%%", percent);
    lv_label_set_text(objects.status_battery_label, buf);
}

void status_bar_set_wifi(bool connected) {
    lv_obj_set_style_text_color(objects.status_wifi_label,
        connected ? lv_color_hex(CLR_WHITE) : lv_color_hex(CLR_GREY), 0);
}

void status_bar_set_time(const char *time_str) {
    lv_label_set_text(objects.status_time_label, time_str);
}

// ─── Tick dispatcher ─────────────────────────────────────────────────────────

typedef void (*tick_screen_func_t)(void);
static tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_scan,
    tick_screen_history,
    tick_screen_settings,
    tick_screen_calibration,
    tick_screen_display_colour,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}

void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

// ─── Fonts ───────────────────────────────────────────────────────────────────

#include "fonts.h"
ext_font_desc_t fonts[] = {
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
};

// ─── Create all screens ──────────────────────────────────────────────────────

void create_screens(void) {
    styles_init();

    eez_flow_init_fonts(fonts, sizeof(fonts) / sizeof(ext_font_desc_t));

    create_screen_scan();
    create_screen_history();
    create_screen_settings();
    create_screen_calibration();
    create_screen_display_colour();
}
