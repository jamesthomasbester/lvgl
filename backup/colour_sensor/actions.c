#include "actions.h"
#include "lv_demo_colour_sensor.h"
#include <stdio.h>

void action_scan_colour(lv_event_t *e) {
    colour_scan_cb_t cb = lv_demo_colour_sensor_get_scan_cb();
    if (cb) {
        uint16_t r = 0, g = 0, b = 0, c = 0;
        cb(r, g, b, c);
    }
}

void action_view_colour(lv_event_t *e) {
    colour_scan_cb_t cb = lv_demo_colour_sensor_get_scan_cb();
    if (cb) {
        uint16_t r = 0, g = 0, b = 0, c = 0;
        cb(r, g, b, c);
    }
}

void action_add_colour(lv_event_t *e) {
    colour_add_cb_t cb = lv_demo_colour_sensor_get_add_cb();
    if(cb){
       printf("Add colour\n"); 
    }
    
}