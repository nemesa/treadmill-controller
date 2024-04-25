//I2C pins:
//SCL -> A5
//SDA -> A4


#include "jojoystick.cpp"
#include "display.cpp"
#include "eeprom.cpp"

#define jX A0
#define jY A1
#define jSW 10

JojoystickHandler jh;
DisplayHandler dh;
EEPROMHandler eh;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup");

  jh.setup(jX,jY,jSW);
  dh.setup();
  eh.setup();

  //eh.readTest();
  
  
}

void loop() {
  jh.loop();
  
  delay(10);
}


