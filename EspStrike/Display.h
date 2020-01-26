#ifndef DISPLAY_H
#define DISPLAY_H


#include <OLED_I2C.h>
#include <Arduino.h>

OLED  myOLED(21, 22); //SDA,SCL

extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

class Display {
  public:
    static void init();
    static void writeText(String text);
};










#endif
