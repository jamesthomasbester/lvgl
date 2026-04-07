#include "lv_demo_colour_sensor.h"
#include "ui.h"

static colour_scan_cb_t _scan_cb = NULL;
static colour_add_cb_t _add_cb = NULL;
static colour_cal_cb_t _cal_cb = NULL;

void lv_demo_colour_sensor_set_add_cb(colour_add_cb_t cb) {
    _add_cb = cb;
}

void lv_demo_colour_sensor_set_scan_cb(colour_scan_cb_t cb) {
    _scan_cb = cb;
}

void lv_demo_colour_sensor_set_calibrate_cb(colour_cal_cb_t cb){
    _cal_cb = cb;
}

colour_scan_cb_t lv_demo_colour_sensor_get_scan_cb(void) {
    return _scan_cb;
}

colour_add_cb_t lv_demo_colour_sensor_get_add_cb(void) {
    return _add_cb;
}

colour_cal_cb_t lv_demo_colour_sensor_get_calibrate_cb(void) {
    return _cal_cb;
}



void lv_demo_colour_sensor(void) {
    ui_init();
}
