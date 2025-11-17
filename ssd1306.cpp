//
// ssd1306.cpp
// 
// Utilities for working with the SSD1306 OLED display
//

#include "ssd1306.h"

#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 SSD1306Utility::Init()
{
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);
  return display;
}

void SSD1306Utility::Setup(Adafruit_SSD1306& display) {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_SCREEN_I2C_ADDRESS);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1); // - a line is 21 chars in this size
  display.setTextColor(WHITE);
  display.display();
}