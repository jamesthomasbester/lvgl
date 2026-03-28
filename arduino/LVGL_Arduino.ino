/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/get-started/platforms/arduino.html  */

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

/*To use the built-in examples and demos of LVGL uncomment the includes below respectively.
 *You also need to copy `lvgl/examples` to `lvgl/src/examples`. Similarly for the demos `lvgl/demos` to `lvgl/src/demos`.
 Note that the `lv_examples` library is for LVGL v7 and you shouldn't install it for this version (since LVGL v8)
 as the examples and demos are now part of the main LVGL library. */

#define EXAMPLE_LVGL_TICK_PERIOD_MS    2
TwoWire I2C_1 = TwoWire(1);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_600MS,  // integration time
  TCS34725_GAIN_1X                 // gain
);

#define SDA_PIN 21
#define SCL_PIN 18

struct colorCalibration {
  unsigned int blackValue;
  unsigned int whiteValue;
};

colorCalibration redCal, greenCal, blueCal;

struct ScanResult {
  int r, g, b;
  char hex[8];
};

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 240;
const uint8_t TCS_ADDR = 0x29;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */
CST816S touch(6, 7, 13, 5);	// sda, scl, rst, irq

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp_drv );
}

void example_increase_lvgl_tick(void *arg)
{
    lv_tick_inc(EXAMPLE_LVGL_TICK_PERIOD_MS);
}

static uint8_t count=0;
void example_increase_reboot(void *arg)
{
  count++;
  if(count==30){
    // esp_restart();
  }
    
}

/*Read the touchpad*/
void my_touchpad_read( lv_indev_drv_t * indev_drv, lv_indev_data_t * data )
{
    // uint16_t touchX, touchY;

    bool touched = touch.available();
    // touch.read_touch();
    if( !touched )
    // if( 0!=touch.data.points )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = touch.data.x;
        data->point.y = touch.data.y;
    }
}

void on_scan_colour(uint16_t r, uint16_t g, uint16_t b, uint16_t c) {
    tcs.getRawData(&r, &g, &b, &c);
    int redValue = RGBmap(r, redCal.blackValue, redCal.whiteValue, 0, 255);
    int greenValue = RGBmap(g, greenCal.blackValue, greenCal.whiteValue, 0, 255);
    int blueValue = RGBmap(b, blueCal.blackValue, blueCal.whiteValue, 0, 255);
    char* hexString = rgbToHex(redValue,greenValue,blueValue);
    Serial.print("R: "); Serial.print(redValue);
    Serial.print(" G: "); Serial.print(greenValue);
    Serial.print(" B: "); Serial.print(blueValue);
    Serial.print(" hex: "); Serial.println(hexString);
    eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_RED_VALUE, eez::Value((int)redValue, eez::VALUE_TYPE_INT32));
    eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_GREEN_VALUE, eez::Value((int)greenValue, eez::VALUE_TYPE_INT32));
    eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_BLUE_VALUE, eez::Value((int)blueValue, eez::VALUE_TYPE_INT32));
    eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_HEX_VALUE, eez::Value(hexString, VALUE_TYPE_STRING));
}

void setup()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug */
    I2C_1.begin(21, 18, 100000);
    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );

    redCal.blackValue = 730;
    redCal.whiteValue = 7147;
    greenCal.blackValue = 1020;
    greenCal.whiteValue = 12217;
    blueCal.blackValue = 1729;
    blueCal.whiteValue = 20051;

    lv_init();
#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

    tft.begin();          /* TFT init */
    tft.setRotation( 0 ); /* Landscape orientation, flipped */
    
    /*Set the touchscreen calibration data,
     the actual data for your display can be acquired using
     the Generic -> Touch_calibrate example from the TFT_eSPI library*/
    // uint16_t calData[5] = { 275, 3620, 264, 3532, 1 };
    // tft.setTouch( calData );
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
    Serial.println( "Setup done" );
}

int RGBmap(unsigned int x, unsigned int inlow, unsigned int inhigh, int outlow, int outhigh){
  float flx = float(x);
  float fla = float(outlow);
  float flb = float(outhigh);
  float flc = float(inlow);
  float fld = float(inhigh);

  float res = ((flx-flc)/(fld-flc))*(flb-fla) + fla;
  
  int result = int(res);
  return constrain(result, outlow, outhigh);
}

const char* rgbToHex(uint8_t r, uint8_t g, uint8_t b) {
  static char hexCol[8];
  sprintf(hexCol, "#%02X%02X%02X", r, g, b);
  return hexCol;
}

void loop()
{
    ui_tick();
    lv_timer_handler(); /* let the GUI do its work */
    delay( 5 );
}
