#include <SoftwareSerial.h>
#include "Arduino.h"

#define ELEMENTS(x) (sizeof(x) / sizeof(x[0]))

class SoftSerialHandler {
public:
  SoftSerialHandler() {
  }
  void setup(int ssRx, int ssTx) {
    Serial.println(F("SoftSerialHandler-setup"));
    sserial = SoftwareSerial(ssRx, ssTx);  // receive pin=10, transmit pin=11
    sserial.begin(9600);
  }

  void sendMain(bool doClean, char* messages) {
    sserial.write("&");
    if (doClean) {
      sserial.write("C+");
    }
    sserial.write("M#");
    sserial.write(messages);
    sserial.write("+");
    sserial.write("$");
  }
  void sendHeader(bool doClean, char* messages) {
    sserial.write("&");
    if (doClean) {
      sserial.write("C+");
    }
    sserial.write("H#");
    sserial.write(messages);
    sserial.write("+");
    sserial.write("$");
  }

  void sendHeaderWithMain(bool doClean, char* headerMessage, char* mainMessage) {
    sserial.write("&");
    if (doClean) {
      sserial.write("C+");
    }
    sserial.write("H#");
    sserial.write(headerMessage);
    sserial.write("+");
    sserial.write("M#");
    sserial.write(mainMessage);
    sserial.write("+");
    sserial.write("$");
  }
  void sendHeaderNavigationWithMain(bool doClean, char* headerMessage, char* nav, char* mainMessage) {
    sserial.write("&");
    if (doClean) {
      sserial.write("C+");
    }
    sserial.write("H#");
    sserial.write(headerMessage);
    sserial.write("+");

    sserial.write("N#");
    sserial.write(nav);
    sserial.write("+");

    sserial.write("M#");
    sserial.write(mainMessage);
    sserial.write("+");

    sserial.write("$");
  }

  void sendHeaderNavigationSmallLines(bool doClean, char* headerMessage, char* nav, char* sl1, char* sl2) {
    sserial.write("&");
    if (doClean) {
      sserial.write("C+");
    }
    sserial.write("H#");
    sserial.write(headerMessage);
    sserial.write("+");

    sserial.write("N#");
    sserial.write(nav);
    sserial.write("+");

    sserial.write("S#");
    sserial.write(sl1);
    sserial.write("+");

    sserial.write("s#");
    sserial.write(sl2);
    sserial.write("+");

    sserial.write("$");
  }

private:
  SoftwareSerial sserial = SoftwareSerial(0, 1);
};