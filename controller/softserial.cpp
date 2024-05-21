#include <SoftwareSerial.h>
#include "Arduino.h"
#include "softserial.h"

SoftSerialHandler::SoftSerialHandler() {
}

void SoftSerialHandler::setup() {
  Serial.println(F("SoftSerialHandler-setup"));
  
  dh.setup();
}

void SoftSerialHandler::sendMain(bool doClean, char* messages) {
  if (doClean) {
    dh.cleanAll();
  }
  dh.main(messages);
}

void SoftSerialHandler::sendHeader(bool doClean, char* messages) {
  if (doClean) {
    dh.cleanAll();
  }
  dh.header(messages);
}

void SoftSerialHandler::sendHeaderWithMain(bool doClean, char* headerMessage, char* mainMessage) {
  if (doClean) {
    dh.cleanAll();
  }
  dh.header(headerMessage);
  dh.main(mainMessage);
}

void SoftSerialHandler::sendHeaderNavigationWithMain(bool doClean, char* headerMessage, bool hasNavUp, bool hasNavLeft, bool hasNavDown, bool hasNavRight, char* mainMessage) {


  if (doClean) {
    dh.cleanAll();
  }
  dh.header(headerMessage);
  dh.navigationOptions(hasNavUp, hasNavLeft, hasNavDown, hasNavRight);
  dh.main(mainMessage);
}

void SoftSerialHandler::sendHeaderNavigationSmallLines(bool doClean, char* headerMessage, bool hasNavUp, bool hasNavLeft, bool hasNavDown, bool hasNavRight, char* sl1, char* sl2) {
  if (doClean) {
    dh.cleanAll();
  }
  dh.header(headerMessage);
  dh.navigationOptions(hasNavUp, hasNavLeft, hasNavDown, hasNavRight);
  dh.mainSmallLine1(sl1);
  dh.mainSmallLine2(sl2);
  
}