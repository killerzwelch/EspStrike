
#include "Display.h"

void Display::init() {
  if(!myOLED.begin(SSD1306_128X32))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...
  myOLED.setFont(SmallFont);

}

void Display::writeText(String text) {

}
