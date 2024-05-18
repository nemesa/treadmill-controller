#include "Arduino.h"
#include "relay.h"

RelayHandler::RelayHandler(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6) {
  _pin1 = pin1;
  _pin2 = pin2;
  _pin3 = pin3;
  _pin4 = pin4;
  _pin5 = pin5;
  _pin6 = pin6;
}

void RelayHandler::setup() {
  Serial.println(F("RelayHandler-setup"));

  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);
  pinMode(_pin3, OUTPUT);
  pinMode(_pin4, OUTPUT);
  pinMode(_pin5, OUTPUT);
  pinMode(_pin6, OUTPUT);
}

void RelayHandler::start() {
  Serial.print(F("RelayHandler-start "));
  Serial.println(_pin1);
}