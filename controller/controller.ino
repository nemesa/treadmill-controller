//I2C pins:
//SCL -> A5
//SDA -> A4

#include <EEPROM.h>
#include "jojoystick.cpp"
#include "displayhandler.cpp"

#define jX A0
#define jY A1
#define jSW 10

JojoystickHandler jh;

DisplayHandler dh;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup");

  jh.setup(jX,jY,jSW);
  dh.setup();
  
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

void loop() {
  jh.loop();
  
  delay(10);
}


