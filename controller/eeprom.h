#ifndef EEPROMHandler_h
#define EEPROMHandler_h

#include "userdata.h"

class EEPROMHandler {
public:
  EEPROMHandler();
  void setup();
  void wipeAll();
  void setLastUser(uint8_t num);
  UserDataStruct getLastSelectedUser();
  void writeUserData(struct UserDataStruct user);
  UserDataStruct readUser(uint8_t num);
private:
};

#endif

