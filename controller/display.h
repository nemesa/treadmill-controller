#ifndef DisplayHandler_h
#define DisplayHandler_h

#include "Arduino.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

class DisplayHandler {
public:
  DisplayHandler();
  void setup();
  void cleanAll();
  void debug(char* text);
  void debug2(char* text);
  void header(char* text);
  void main(char* text);
  void mainSmallLine1(char* text);
  void mainSmallLine2(char* text);
  void navigationOptions(bool hasUp, bool hasLeft, bool hasDown, bool hasRight);
private:
  Adafruit_SSD1306 display;
};

#endif