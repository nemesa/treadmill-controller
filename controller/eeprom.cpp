#include <EEPROM.h>
#include "Arduino.h"
#include "user.h"



class EEPROMHandler {
public:

  void setup() {
    Serial.println("EEPROMHandler-setup");
    struct UserDataStruct defaultUser;

    defaultUser.walkSpeed = 51;
    defaultUser.runSpeed = 71;
    defaultUser.lastSelection = 1;
    if (EEPROM.read(10) == 255) {
      Serial.println("EEPROMHandler-add default user 1");
      defaultUser.num = 1;
      defaultUser.name = "user__1";
      writeUserData(defaultUser);
    }

    if (EEPROM.read(20) == 255) {
      Serial.println("EEPROMHandler-add default user 2");
      defaultUser.num = 2;
      defaultUser.name = "user__2";
      writeUserData(defaultUser);
    }

    if (EEPROM.read(30) == 255) {
      Serial.println("EEPROMHandler-add default user 3");
      defaultUser.num = 3;
      defaultUser.name = "user3";
      writeUserData(defaultUser);
    }

    if (EEPROM.read(40) == 255) {
      Serial.println("EEPROMHandler-add default user 4");
      defaultUser.num = 4;
      defaultUser.name = "user4";
      writeUserData(defaultUser);
    }
    readTest();
  }
  void readTest() {
    for (int i = 0; i <= 30; i++) {  //i max = 512
      int eepromValue = EEPROM.read(i);
      Serial.print("address: ");
      Serial.print(i);
      Serial.print("value: ");
      Serial.println(eepromValue);
    }

    // if (EEPROM.read(5) != 12) {
    //   EEPROM.write(5, 12);
    // }
  }
  //void writeUserData(uint8_t userNo, char* name, uint8_t walkSpeed, uint8_t runSpeed, uint8_t lastSelection) {
  void writeUserData(struct UserDataStruct user) {

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
  UserDataStruct readUser(uint8_t num) {
    struct UserDataStruct user;
    user.num = num;
    user.name = "";
    char name[6];
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
};