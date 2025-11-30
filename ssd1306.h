//
// ssd1306.h
// 
// Utilities for working with the SSD1306 OLED display
//

#ifndef SSD1306_H
#define SSD1306_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// These defines were taken from one of the worksheets
#define OLED_RESET -1
#define OLED_SCREEN_I2C_ADDRESS 0x3C
#define SCREEN_WIDTH 128             // OLED display width, in pixels
#define SCREEN_HEIGHT 64             // OLED display height, in pixels

class SSD1306Utility
{
public:
  // initialise and return the OLED display
  static Adafruit_SSD1306 Init();

  // setup the OLED display. Intended to be put in the setup() function
  static void Setup(Adafruit_SSD1306& display);
};

#endif // SSD1306_H