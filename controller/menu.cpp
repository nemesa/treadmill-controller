#include "Arduino.h"
#include "display.cpp"
#include "eeprom.cpp"

class MenuHandler {
public:

  void setup() {
    Serial.println("MenuHandler-setup");
    dh.setup();
    eh.setup();
    startScreen();
  }
  void down() {
    dh.debug("|down");
  }
  void up() {
    dh.debug("|up");
  }
  void left() {
    dh.debug("|left");
  }
  void right() {
    dh.debug("|right");
  }
  void select() {
    dh.debug("select");
  }

private:
  void startScreen() {
    dh.cleanAll();
    dh.header("Welcome!");
  }
  DisplayHandler dh;
  EEPROMHandler eh;
};