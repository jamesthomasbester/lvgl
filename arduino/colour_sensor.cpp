#include "colour_sensor.h"
#include <demos/colour_sensor/vars.h>
#include <eez/flow/flow.h>
#include <demos/colour_sensor/ui.h>

TwoWire I2C_1 = TwoWire(1);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(
    TCS34725_INTEGRATIONTIME_600MS,
    TCS34725_GAIN_1X
);

colorCalibration redCal, greenCal, blueCal;

void colour_sensor_init() {
    I2C_1.begin(SDA_PIN, SCL_PIN, 100000);
    redCal.blackValue = 674;
    redCal.whiteValue = 6369;
    greenCal.blackValue = 925;
    greenCal.whiteValue = 10839;
    blueCal.blackValue = 1610;
    blueCal.whiteValue = 18057;
    if (tcs.begin(TCS_ADDR, &I2C_1)) {
        Serial.println("TCS34725 found!");
    }
}

void calibrate_colour() {
    if(eez::flow::getGlobalVariable(FLOW_GLOBAL_VARIABLE_CALIBRATION_COMPLETED) == false) {
        uint16_t br,bg,bb,bc = colour_calibration_black();
    }else if(eez::flow::getGlobalVariable(FLOW_GLOBAL_VARIABLE_CALIBRATION_COMPLETED) == true) {
        uint16_t wr,wg,wb,wc = colour_calibration_white();
        redCal.blackValue = br;
        redCal.whiteValue = wr;
        greenCal.blackValue = bg;
        greenCal.whiteValue = wg;
        blueCal.blackValue = bb;
        blueCal.whiteValue = wb;
        eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_CALIBRATION_COMPLETED, eez::Value((bool)false,   eez::VALUE_TYPE_BOOLEAN));
    } 
}

uint16_t colour_calibration_black() {
    tcs.getRawData(&br, &bg, &bb, &bc);
    eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_CALIBRATION_COMPLETED, eez::Value((bool)true,   eez::VALUE_TYPE_BOOLEAN));
    return br,bg,bb,bc;
}

uint16_t colour_calibration_white() {
    tcs.getRawData(&wr, &wg, &wb, &wc);
    return wr,wg,wb,wc;
}

void on_scan_colour(uint16_t r, uint16_t g, uint16_t b, uint16_t c) {
    tcs.getRawData(&r, &g, &b, &c);
    int redValue   = RGBmap(r, redCal.blackValue,   redCal.whiteValue,   0, 255);
    int greenValue = RGBmap(g, greenCal.blackValue, greenCal.whiteValue, 0, 255);
    int blueValue  = RGBmap(b, blueCal.blackValue,  blueCal.whiteValue,  0, 255);
    Serial.print("R: "); Serial.print(r);
    Serial.print(" G: "); Serial.print(g);
    Serial.print(" B: "); Serial.print(b);
    Serial.print(" hex: "); Serial.println(rgbToHex(redValue, greenValue, blueValue));
    set_var_hex_value(rgbToHex(redValue, greenValue, blueValue));
    set_var_history_value(rgbToHex(redValue, greenValue, blueValue));
    eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_RED_VALUE,   eez::Value((int)redValue,   eez::VALUE_TYPE_INT32));
    eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_GREEN_VALUE, eez::Value((int)greenValue, eez::VALUE_TYPE_INT32));
    eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_BLUE_VALUE,  eez::Value((int)blueValue,  eez::VALUE_TYPE_INT32));
    eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_HEX_VALUE,   eez::Value(rgbToHex(redValue, greenValue, blueValue), eez::VALUE_TYPE_STRING));
}

int RGBmap(unsigned int x, unsigned int inlow, unsigned int inhigh, int outlow, int outhigh) {
    float res = ((float(x) - float(inlow)) / (float(inhigh) - float(inlow))) * (float(outhigh) - float(outlow)) + float(outlow);
    return constrain((int)res, outlow, outhigh);
}

const char* rgbToHex(uint8_t r, uint8_t g, uint8_t b) {
    static char hexCol[8];
    sprintf(hexCol, "#%02X%02X%02X", r, g, b);
    return hexCol;
}
