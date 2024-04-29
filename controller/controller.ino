//I2C pins:
//SCL -> A5
//SDA -> A4


#include "jojoystick.cpp"
#include "menu.cpp"

#define jX A0
#define jY A1
#define jSW 4

JojoystickHandler jh;
MenuHandler mh;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup");

  jh.setup(jX, jY, jSW);
  mh.setup();

  //eh.readTest();
}

void loop() {
  jh.loop();
  if (jh.isDownReleased()) {
    mh.down();
  }
  if (jh.isUpReleased()) {
    mh.up();
  }
  if (jh.isLeftReleased()) {
    mh.left();
  }
  if (jh.isRightReleased()) {
    mh.right();
  }
  if (jh.isSWReleased()) {
    mh.select();
  }

  delay(10);
}
