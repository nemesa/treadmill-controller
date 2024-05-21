#ifndef SoftSerial_h
#define SoftSerial_h

#include "display.h"

class SoftSerialHandler {
public:
  SoftSerialHandler();
  void setup();
  void sendMain(bool doClean, char* messages);
  void sendHeader(bool doClean, char* messages);
  void sendHeaderWithMain(bool doClean, char* headerMessage, char* mainMessage);
  void sendHeaderNavigationWithMain(bool doClean, char* headerMessage, bool hasNavUp, bool hasNavLeft, bool hasNavDown, bool hasNavRight, char* mainMessage);
  void sendHeaderNavigationSmallLines(bool doClean, char* headerMessage, bool hasNavUp, bool hasNavLeft, bool hasNavDown, bool hasNavRight, char* sl1, char* sl2);
private:
  DisplayHandler dh;
};

#endif