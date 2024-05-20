#ifndef SoftSerial_h
#define SoftSerial_h

#include <SoftwareSerial.h>
#include "display.h"

class SoftSerialHandler {
public:
  SoftSerialHandler();
  SoftSerialHandler(short ssRx, short ssTx);
  void setup();
  void sendMain(bool doClean, char* messages);
  void sendHeader(bool doClean, char* messages);
  void sendHeaderWithMain(bool doClean, char* headerMessage, char* mainMessage);
  void sendHeaderNavigationWithMain(bool doClean, char* headerMessage, char* nav, char* mainMessage);
  void sendHeaderNavigationSmallLines(bool doClean, char* headerMessage, char* nav, char* sl1, char* sl2);
private:
  short _ssRx = 0;
  short _ssTx = 0;
  SoftwareSerial sserial = SoftwareSerial(0, 1);
  DisplayHandler dh;
};

#endif