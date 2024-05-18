#include "Arduino.h"
#include "relay.h"

RelayHandler::RelayHandler(int pin) {
  _pin = pin;
}

void RelayHandler::setup() {
  Serial.println(F("RelayHandler-setup"));

  pinMode(_pin, OUTPUT);
}

void RelayHandler::start() {
  Serial.print(F("RelayHandler-start "));
  Serial.println(_pin);
}