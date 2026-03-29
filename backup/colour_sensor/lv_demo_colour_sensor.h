#ifndef LV_DEMO_COLOUR_SENSOR_H
#define LV_DEMO_COLOUR_SENSOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*colour_scan_cb_t)(uint16_t r, uint16_t g, uint16_t b, uint16_t c);

void lv_demo_colour_sensor(void);
void lv_demo_colour_sensor_set_scan_cb(colour_scan_cb_t cb);

#ifdef __cplusplus
}
#endif

#endif /*LV_DEMO_COLOUR_SENSOR_H*/
