#include <EEPROM.h>
#include "Arduino.h"

class EEPROMHandler {
public:

  void setup() {
    Serial.println("EEPROMHandler-setup");
  }
  void readTest() {
    for (int i = 0; i <= 10; i++) {  //i max = 512
      int eepromValue = EEPROM.read(i);
      Serial.print("address: ");
      Serial.print(i);
      Serial.print("value: ");
      Serial.println(eepromValue);
    }

    if (EEPROM.read(5) != 12) {
      EEPROM.write(5, 12);
    }
  }
};