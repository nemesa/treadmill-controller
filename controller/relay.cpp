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
  Serial.println(F("RelayHandler-start "));
  if (!isRunning) {
    isRunning = true;
  }
}

void RelayHandler::stop() {
  Serial.println(F("RelayHandler-stop "));
  if (isRunning) {
    isRunning = false;
  }
}
void RelayHandler::toSpeed(uint8_t speed) {
  Serial.print(F("RelayHandler-speed "));
  Serial.println(speed);
}

void RelayHandler::pinTest(uint8_t pinNo) {
  Serial.print(F("RelayHandler-pinTest "));
  Serial.println(pinNo);
  if (pinNo > 0 && pinNo < 7) {
    sendSignal(pinNo);
  } else {
    sendSignal(1);
  }
}

void RelayHandler::sendSignal(uint8_t pinNo) {
  uint8_t pin = _pin1;
  if (pinNo == 2) {
    pin = _pin2;
  }
  if (pinNo == 3) {
    pin = _pin3;
  }
  if (pinNo == 4) {
    pin = _pin4;
  }
  if (pinNo == 5) {
    pin = _pin5;
  }
  if (pinNo == 6) {
    pin = _pin6;
  }


  digitalWrite(pin, HIGH);
  delay(50);
  digitalWrite(pin, LOW);
}
