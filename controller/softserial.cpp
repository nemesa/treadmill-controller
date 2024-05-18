#include <SoftwareSerial.h>
#include "Arduino.h"
#include "softserial.h"

SoftSerialHandler::SoftSerialHandler(short ssRx, short ssTx) {
  _ssRx = ssRx;
  _ssTx = ssTx;
}

void SoftSerialHandler::setup() {
  Serial.println(F("SoftSerialHandler-setup"));
  sserial = SoftwareSerial(_ssRx, _ssTx);
  sserial.begin(9600);
}

void SoftSerialHandler::sendMain(bool doClean, char* messages) {
  sserial.write("&");
  if (doClean) {
    sserial.write("C+");
  }
  sserial.write("M#");
  sserial.write(messages);
  sserial.write("+");
  sserial.write("$");
}

void SoftSerialHandler::sendHeader(bool doClean, char* messages) {
  sserial.write("&");
  if (doClean) {
    sserial.write("C+");
  }
  sserial.write("H#");
  sserial.write(messages);
  sserial.write("+");
  sserial.write("$");
}

void SoftSerialHandler::sendHeaderWithMain(bool doClean, char* headerMessage, char* mainMessage) {
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

void SoftSerialHandler::sendHeaderNavigationWithMain(bool doClean, char* headerMessage, char* nav, char* mainMessage) {
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

void SoftSerialHandler::sendHeaderNavigationSmallLines(bool doClean, char* headerMessage, char* nav, char* sl1, char* sl2) {
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