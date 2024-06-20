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
  void header(bool doClean,char* text);
  void main(bool doClean,char* text);
  void mainSmallLine1(char* text);
  void mainSmallLine2(char* text);
  void navigationOptions(bool hasUp, bool hasLeft, bool hasDown, bool hasRight);

  
  void progressBar(byte pecentage);
  
  void headerWithMain(bool doClean, char* headerMessage, char* mainMessage);
  void headerNavigationWithMain(bool doClean, char* headerMessage, bool hasNavUp, bool hasNavLeft, bool hasNavDown, bool hasNavRight, char* mainMessage);
  void headerNavigationSmallLines(bool doClean, char* headerMessage, bool hasNavUp, bool hasNavLeft, bool hasNavDown, bool hasNavRight, char* sl1, char* sl2);
private:
  Adafruit_SSD1306 display;
};

#endif