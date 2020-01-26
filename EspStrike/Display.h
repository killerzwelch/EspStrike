#ifndef DISPLAY_H
#define DISPLAY_H


#include <OLED_I2C.h>
#include <Arduino.h>

extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

class Display {
  public:
    static void init();
    static void writeText(String text);
    static void printPlayer();
    static void startup();
};










#endif
