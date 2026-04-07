#include "styles.h"

lv_style_t style_screen;
lv_style_t style_surface;
lv_style_t style_accent_btn;
lv_style_t style_ghost_btn;
lv_style_t style_label_title;
lv_style_t style_label_accent;
lv_style_t style_label_body;
lv_style_t style_label_grey;
lv_style_t style_status_bar;
lv_style_t style_divider;
lv_style_t style_table;

void styles_init(void) {
    // Base screen
    lv_style_init(&style_screen);
    lv_style_set_bg_color(&style_screen, lv_color_hex(CLR_BG));
    lv_style_set_bg_opa(&style_screen, LV_OPA_COVER);
    lv_style_set_border_width(&style_screen, 0);
    lv_style_set_pad_all(&style_screen, 0);
    lv_style_set_text_color(&style_screen, lv_color_hex(CLR_WHITE));
    lv_style_set_text_font(&style_screen, &lv_font_montserrat_12);

    // Surface card
    lv_style_init(&style_surface);
    lv_style_set_bg_color(&style_surface, lv_color_hex(CLR_SURFACE));
    lv_style_set_bg_opa(&style_surface, LV_OPA_COVER);
    lv_style_set_border_color(&style_surface, lv_color_hex(CLR_BORDER));
    lv_style_set_border_width(&style_surface, 1);
    lv_style_set_radius(&style_surface, 4);
    lv_style_set_pad_all(&style_surface, 8);

    // Accent (red) button
    lv_style_init(&style_accent_btn);
    lv_style_set_bg_color(&style_accent_btn, lv_color_hex(CLR_ACCENT));
    lv_style_set_bg_opa(&style_accent_btn, LV_OPA_COVER);
    lv_style_set_border_width(&style_accent_btn, 0);
    lv_style_set_radius(&style_accent_btn, 4);
    lv_style_set_text_color(&style_accent_btn, lv_color_hex(CLR_WHITE));
    lv_style_set_text_font(&style_accent_btn, &lv_font_montserrat_12);
    lv_style_set_pad_ver(&style_accent_btn, 8);
    lv_style_set_pad_hor(&style_accent_btn, 16);

    // Ghost (outline) button
    lv_style_init(&style_ghost_btn);
    lv_style_set_bg_opa(&style_ghost_btn, LV_OPA_TRANSP);
    lv_style_set_border_color(&style_ghost_btn, lv_color_hex(CLR_BORDER));
    lv_style_set_border_width(&style_ghost_btn, 1);
    lv_style_set_radius(&style_ghost_btn, 4);
    lv_style_set_text_color(&style_ghost_btn, lv_color_hex(CLR_WHITE));
    lv_style_set_text_font(&style_ghost_btn, &lv_font_montserrat_12);
    lv_style_set_pad_ver(&style_ghost_btn, 8);
    lv_style_set_pad_hor(&style_ghost_btn, 16);

    // Title label
    lv_style_init(&style_label_title);
    lv_style_set_text_color(&style_label_title, lv_color_hex(CLR_WHITE));
    lv_style_set_text_font(&style_label_title, &lv_font_montserrat_16);

    // Accent label (red, small caps style)
    lv_style_init(&style_label_accent);
    lv_style_set_text_color(&style_label_accent, lv_color_hex(CLR_ACCENT));
    lv_style_set_text_font(&style_label_accent, &lv_font_montserrat_10);

    // Body label
    lv_style_init(&style_label_body);
    lv_style_set_text_color(&style_label_body, lv_color_hex(CLR_WHITE));
    lv_style_set_text_font(&style_label_body, &lv_font_montserrat_12);

    // Grey/muted label
    lv_style_init(&style_label_grey);
    lv_style_set_text_color(&style_label_grey, lv_color_hex(CLR_GREY));
    lv_style_set_text_font(&style_label_grey, &lv_font_montserrat_10);

    // Status bar
    lv_style_init(&style_status_bar);
    lv_style_set_bg_color(&style_status_bar, lv_color_hex(CLR_BG));
    lv_style_set_bg_opa(&style_status_bar, LV_OPA_COVER);
    lv_style_set_border_width(&style_status_bar, 0);
    lv_style_set_border_side(&style_status_bar, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_border_color(&style_status_bar, lv_color_hex(CLR_BORDER));
    lv_style_set_pad_hor(&style_status_bar, 8);
    lv_style_set_pad_ver(&style_status_bar, 0);
    lv_style_set_radius(&style_status_bar, 0);

    // Divider line
    lv_style_init(&style_divider);
    lv_style_set_bg_color(&style_divider, lv_color_hex(CLR_ACCENT));
    lv_style_set_bg_opa(&style_divider, LV_OPA_COVER);
    lv_style_set_border_width(&style_divider, 0);
    lv_style_set_radius(&style_divider, 0);

    // Table
    lv_style_init(&style_table);
    lv_style_set_bg_color(&style_table, lv_color_hex(CLR_SURFACE));
    lv_style_set_bg_opa(&style_table, LV_OPA_COVER);
    lv_style_set_border_color(&style_table, lv_color_hex(CLR_BORDER));
    lv_style_set_border_width(&style_table, 1);
    lv_style_set_text_color(&style_table, lv_color_hex(CLR_WHITE));
    lv_style_set_text_font(&style_table, &lv_font_montserrat_10);
    lv_style_set_pad_all(&style_table, 4);
}
