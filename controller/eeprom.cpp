#include <EEPROM.h>
#include "Arduino.h"
#include "userdata.h"
#include "eeprom.h"

EEPROMHandler::EEPROMHandler() {  
}

void EEPROMHandler::setup() {
  Serial.println(F("EEPROMHandler-setup"));
  struct UserDataStruct defaultUser;

  defaultUser.walkSpeed = 51;
  defaultUser.runSpeed = 71;
  defaultUser.lastSelection = 1;
  if (EEPROM.read(10) == 255) {
    defaultUser.num = 1;
    defaultUser.name = "user__1";
    writeUserData(defaultUser);
  }

  if (EEPROM.read(20) == 255) {
    defaultUser.num = 2;
    defaultUser.name = "user__2";
    writeUserData(defaultUser);
  }

  if (EEPROM.read(30) == 255) {
    defaultUser.num = 3;
    defaultUser.name = "user3";
    writeUserData(defaultUser);
  }

  if (EEPROM.read(40) == 255) {
    defaultUser.num = 4;
    defaultUser.name = "user4";
    writeUserData(defaultUser);
  }
}

void EEPROMHandler::wipeAll() {
  for (int i = 0; i <= 512; i++) {
    EEPROM.write(i, 255);
  }
}

void EEPROMHandler::setLastUser(uint8_t num) {
  EEPROM.update(0, num);
}

UserDataStruct EEPROMHandler::getLastSelectedUser() {
  uint8_t lastUser = EEPROM.read(0);
  if (lastUser > 4) {
    lastUser = 1;
  }
  return readUser(lastUser);
}

void EEPROMHandler::writeUserData(struct UserDataStruct user) {

  uint8_t offset = user.num * 10;
  int len = strlen(user.name);
  for (int i = 0; i <= 6; i++) {
    if (i >= len) {
      EEPROM.update(offset + i, ' ');
    } else {
      EEPROM.update(offset + i, user.name[i]);
    }
  }
  EEPROM.update(offset + 7, user.walkSpeed);
  EEPROM.update(offset + 8, user.runSpeed);
  EEPROM.update(offset + 9, user.lastSelection);
}

UserDataStruct EEPROMHandler::readUser(uint8_t num) {
  struct UserDataStruct user;
  user.num = num;
  user.name = "";
  char* name = "       ";
  uint8_t offset = user.num * 10;
  for (int i = 0; i <= 6; i++) {
    name[i] = (char)EEPROM.read(offset + i);
  }
  user.name = name;
  user.walkSpeed = EEPROM.read(offset + 7);
  user.runSpeed = EEPROM.read(offset + 8);
  user.lastSelection = EEPROM.read(offset + 9);

  return user;
}
