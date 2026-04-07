#include "ui.h"
#include "screens.h"
#include "images.h"
#include "actions.h"
#include "vars.h"

void ui_init() {
    create_screens();
    lv_scr_load(objects.scan);
}

void ui_tick() {
    lv_obj_t *active = lv_scr_act();
    if      (active == objects.scan)           tick_screen_scan();
    else if (active == objects.history)        tick_screen_history();
    else if (active == objects.settings)       tick_screen_settings();
    else if (active == objects.calibration)    tick_screen_calibration();
    else if (active == objects.display_colour) tick_screen_display_colour();
}
