#include "lv_demo_colour_sensor.h"
#include "ui.h"

static colour_scan_cb_t _scan_cb = NULL;

void lv_demo_colour_sensor_set_scan_cb(colour_scan_cb_t cb) {
    _scan_cb = cb;
}

colour_scan_cb_t lv_demo_colour_sensor_get_scan_cb(void) {
    return _scan_cb;
}

void lv_demo_colour_sensor(void) {
    ui_init();
}
