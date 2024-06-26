#include <EEPROM.h>
#include "Arduino.h"
#include "userdata.h"
#include "eeprom.h"
#include "controlpinmap.h"

EEPROMHandler::EEPROMHandler() {
}

void EEPROMHandler::setup() {
  Serial.println(F("EEPROMHandler-setup"));
  //wipeAll();
  struct ControlPinMapStruct defaultMap;
  defaultMap.startStop = 3;
  defaultMap.speedInc = 2;
  defaultMap.speedDec = 1;
  defaultMap.speed30 = 6;
  defaultMap.speed60 = 5;
  defaultMap.speed100 = 4;
  defaultMap.holdDelay = 7;
  defaultMap.pressDelay = 10;


  if (EEPROM.read(0) == 255) {
    EEPROM.update(0, 1);
  }

  if (EEPROM.read(1) == 255) {
    EEPROM.update(1, defaultMap.startStop);
  }
  if (EEPROM.read(2) == 255) {
    EEPROM.update(2, defaultMap.speedInc);
  }
  if (EEPROM.read(3) == 255) {
    EEPROM.update(3, defaultMap.speedDec);
  }
  if (EEPROM.read(4) == 255) {
    EEPROM.update(4, defaultMap.speed30);
  }
  if (EEPROM.read(5) == 255) {
    EEPROM.update(5, defaultMap.speed60);
  }
  if (EEPROM.read(6) == 255) {
    EEPROM.update(6, defaultMap.speed100);
  }
  if (EEPROM.read(7) == 255) {
    EEPROM.update(7, defaultMap.holdDelay);
  }
  if (EEPROM.read(8) == 255) {
    EEPROM.update(8, defaultMap.pressDelay);
  }


  struct UserDataStruct defaultUser;
  defaultUser.walkSpeed = 51;
  defaultUser.runSpeed = 71;
  defaultUser.lastSelection = 1;
  defaultUser.name = "u1     ";

  if (EEPROM.read(10) == 255) {
    defaultUser.num = 1;
    defaultUser.name[1] = (char)49;  //1
    writeUserData(defaultUser);
  }

  if (EEPROM.read(20) == 255) {
    defaultUser.num = 2;
    defaultUser.name[1] = (char)50;  //2
    writeUserData(defaultUser);
  }

  if (EEPROM.read(30) == 255) {
    defaultUser.num = 3;
    defaultUser.name[1] = (char)51;  //3
    writeUserData(defaultUser);
  }

  if (EEPROM.read(40) == 255) {
    defaultUser.num = 4;
    defaultUser.name[1] = (char)52;  //4
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
  for (byte i = 0; i <= 6; i++) {
    EEPROM.update(offset + i, user.name[i]);
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
  for (byte i = 0; i <= 6; i++) {
    name[i] = (char)EEPROM.read(offset + i);
  }
  user.name = name;
  user.walkSpeed = EEPROM.read(offset + 7);
  user.runSpeed = EEPROM.read(offset + 8);
  user.lastSelection = EEPROM.read(offset + 9);

  return user;
}

ControlPinMapStruct EEPROMHandler::getControlPinMap() {

  struct ControlPinMapStruct map;
  map.startStop = EEPROM.read(1);
  map.speedInc = EEPROM.read(2);
  map.speedDec = EEPROM.read(3);
  map.speed30 = EEPROM.read(4);
  map.speed60 = EEPROM.read(5);
  map.speed100 = EEPROM.read(6);
  map.holdDelay = EEPROM.read(7);
  map.pressDelay = EEPROM.read(8);


  Serial.println(F("EEPROMHandler-getControlPinMap"));
  Serial.print(map.startStop);
  Serial.print(F(" - "));
  Serial.print(map.speedInc);
  Serial.print(F(" - "));
  Serial.print(map.speedDec);
  Serial.print(F(" - "));
  Serial.print(map.speed30);
  Serial.print(F(" - "));
  Serial.print(map.speed60);
  Serial.print(F(" - "));
  Serial.print(map.speed100);
  Serial.print(F(" - "));
  Serial.print(map.holdDelay);
  Serial.print(F(" - "));
  Serial.println(map.pressDelay);

  return map;
}

void EEPROMHandler::writeControlPinMap(struct ControlPinMapStruct map) {
  Serial.println(F("EEPROMHandler-writeControlPinMap"));
  Serial.print(map.startStop);
  Serial.print(F(" - "));
  Serial.print(map.speedInc);
  Serial.print(F(" - "));
  Serial.print(map.speedDec);
  Serial.print(F(" - "));
  Serial.print(map.speed30);
  Serial.print(F(" - "));
  Serial.print(map.speed60);
  Serial.print(F(" - "));
  Serial.print(map.speed100);
  Serial.print(F(" - "));
  Serial.print(map.holdDelay);
  Serial.print(F(" - "));
  Serial.println(map.pressDelay);

  EEPROM.update(1, map.startStop);
  EEPROM.update(2, map.speedInc);
  EEPROM.update(3, map.speedDec);
  EEPROM.update(4, map.speed30);
  EEPROM.update(5, map.speed60);
  EEPROM.update(6, map.speed100);
  EEPROM.update(7, map.holdDelay);
  EEPROM.update(8, map.pressDelay);
}
