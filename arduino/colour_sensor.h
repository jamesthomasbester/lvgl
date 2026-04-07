#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <lvgl.h>
#include "Adafruit_TCS34725.h"

#define SDA_PIN 21
#define SCL_PIN 18
const uint8_t TCS_ADDR = 0x29;
struct colorCalibration {
    unsigned int blackValue;
    unsigned int whiteValue;
};
uint16_t br,bg,bb,bc;
uint16_t wr,wg,wb,wc;

extern TwoWire I2C_1;
extern Adafruit_TCS34725 tcs;
extern colorCalibration redCal, greenCal, blueCal;

void colour_sensor_init();
void on_scan_colour(uint16_t r, uint16_t g, uint16_t b, uint16_t c);
void calibrate_colour();
uint16_t colour_calibration_black();
uint16_t colour_calibration_white();
int RGBmap(unsigned int x, unsigned int inlow, unsigned int inhigh, int outlow, int outhigh);
const char* rgbToHex(uint8_t r, uint8_t g, uint8_t b);
