#include <lvgl.h>
#include <TFT_eSPI.h>
#include "lv_conf.h"
#include <Wire.h>
#include <demos/lv_demos.h>
#include <demos/colour_sensor/lv_demo_colour_sensor.h>
#include <demos/colour_sensor/ui.h>
#include <demos/colour_sensor/vars.h>
#include <eez/flow/flow.h>
#include "CST816S.h"
#include "Adafruit_TCS34725.h"
#include "colour_sensor.h"
#include "display.h"

#define EXAMPLE_LVGL_TICK_PERIOD_MS    2

struct ScanResult {
  int r, g, b;
  char hex[8];
};

static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 240;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

#if LV_USE_LOG != 0
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

static uint8_t count=0;

void setup()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug */
    I2C_1.begin(21, 18, 100000);
    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );

    redCal.blackValue = 674;
    redCal.whiteValue = 6369;
    greenCal.blackValue = 925;
    greenCal.whiteValue = 10839;
    blueCal.blackValue = 1610;
    blueCal.whiteValue = 18057;

    lv_init();
#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

    tft.begin();          /* TFT init */
    tft.setRotation( 0 ); /* Landscape orientation, flipped */
    touch.begin();
    if (tcs.begin(TCS_ADDR, &I2C_1)) {
        Serial.println("TCS34725 found!");
    }
    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );
  
    /* Create simple label */
    lv_obj_t *label = lv_label_create( lv_scr_act() );
    lv_label_set_text( label, "Hello Ardino and LVGL!");
    lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
   
    const esp_timer_create_args_t lvgl_tick_timer_args = {
      .callback = &example_increase_lvgl_tick,
      .name = "lvgl_tick"
    };

    const esp_timer_create_args_t reboot_timer_args = {
      .callback = &example_increase_reboot,
      .name = "reboot"
    };

    esp_timer_handle_t lvgl_tick_timer = NULL;
    esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer);
    esp_timer_start_periodic(lvgl_tick_timer, EXAMPLE_LVGL_TICK_PERIOD_MS * 1000);

    esp_timer_handle_t reboot_timer = NULL;
    esp_timer_create(&reboot_timer_args, &reboot_timer);
    esp_timer_start_periodic(reboot_timer, 2000 * 1000);      
    lv_demo_colour_sensor();
    lv_demo_colour_sensor_set_scan_cb(on_scan_colour);
    lv_demo_colour_sensor_set_add_cb(on_scan_colour);
    lv_demo_colour_sensor_set_calibrate_cb(calibrate_colour);
    Serial.println( "Setup done" );
}

void loop()
{
    ui_tick();
    lv_timer_handler(); /* let the GUI do its work */
    delay( 5 );
}
