
#include "Display.h"
#include "Player.h"

static OLED myOLED(21, 22); //SDA,SCL


void Display::init() {
  if(!myOLED.begin(SSD1306_128X32))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...
  myOLED.setFont(SmallFont);

}

void Display::startup(){
  myOLED.print("Starting up...",CENTER,0);
  myOLED.print("Waiting for Config",CENTER,12);
  myOLED.print(System::ipaddress, CENTER, 24);
  myOLED.update();
}

void Display::writeText(String text) {
  myOLED.print(text, CENTER, 12);
  myOLED.update();
}

void Display::printPlayer(){
  if(System::configReceived) {
    myOLED.clrScr();
    myOLED.print("Player: " + String(Player::player),LEFT,0);
    myOLED.print("Team: " + String(Player::team),RIGHT,0);
    myOLED.print(String(Player::health) + "/" + String(Player::maxHealth) + " (" + String(Player::life) +")",RIGHT,12);
    myOLED.update();
  }
}
