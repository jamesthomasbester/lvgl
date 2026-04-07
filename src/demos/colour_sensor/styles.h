#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include "../../lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

// Theme colours
#define CLR_BG        0x0D0D0D
#define CLR_SURFACE   0x1A1A1A
#define CLR_BORDER    0x2A2A2A
#define CLR_ACCENT    0xE63030
#define CLR_WHITE     0xFFFFFF
#define CLR_GREY      0x888888
#define CLR_SCAN_BTN  0x1A1A1A

extern lv_style_t style_screen;
extern lv_style_t style_surface;
extern lv_style_t style_accent_btn;
extern lv_style_t style_ghost_btn;
extern lv_style_t style_label_title;
extern lv_style_t style_label_accent;
extern lv_style_t style_label_body;
extern lv_style_t style_label_grey;
extern lv_style_t style_status_bar;
extern lv_style_t style_divider;
extern lv_style_t style_table;

void styles_init(void);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/
