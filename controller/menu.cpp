#include "Arduino.h"
#include "display.cpp"
#include "eeprom.cpp"

class MenuHandler {
public:

  void setup() {
    Serial.println("MenuHandler-setup");
    dh.setup();
    eh.setup();

    user = eh.getLastSelectedUser();

    startScreen();
  }
  void down() {
    if (isStartScreen) {
      startScreenDown();
    }
  }
  void up() {
    if (isStartScreen) {
      startScreenUp();
    }
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
    isStartScreen = true;
    dh.cleanAll();
    dh.header("Welcome!");
    dh.main(user.name);
  }
  void startScreenDown() {
    uint8_t num = user.num + 1;
    if (num > 4) {
      num = 1;
    }
    user = eh.readUser(num);
    dh.main(user.name);
  }
  void startScreenUp() {
    uint8_t num = user.num - 1;
    if (num == 0) {
      num = 4;
    }
    user = eh.readUser(num);
    dh.main(user.name);
  }
  bool isStartScreen;
  UserDataStruct user;
  DisplayHandler dh;
  EEPROMHandler eh;
};