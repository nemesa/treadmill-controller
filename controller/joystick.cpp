#include "Arduino.h"
#include "joystick.h"

JoystickHandler::JoystickHandler(uint8_t pinX, uint8_t pinY, uint8_t pinSW) {
  _pinX = pinX;
  _pinY = pinY;
  _pinSW = pinSW;
}

void JoystickHandler::setup() {
  Serial.println(F("JojoystickHandler-setup"));

  pinMode(_pinX, INPUT);
  pinMode(_pinY, INPUT);
  pinMode(_pinSW, INPUT_PULLUP);
  _isLeft = false;
  _isRight = false;
  _isUp = false;
  _isDown = false;
  _isSW = false;
  _lastButtonPress = 0;
}


void JoystickHandler::loop() {

  _isLeftReleased = false;
  _isRightReleased = false;
  _isUpReleased = false;
  _isDownReleased = false;
  _isSWReleased = false;
  _x = analogRead(_pinX);
  _y = analogRead(_pinY);
  if (digitalRead(_pinSW) == 0) {

    if (!_isSW) {
      _lastButtonPress = millis();
    }
    _isSW = true;
  } else {
    if (_isSW && _lastButtonPress + 100 < millis()) {
      swReleased();
    }
  }


  if (_x < 100) {
    _isLeft = true;
    if (_isRight) {
      rightReleased();
    }
    _isRight = false;
  } else if (_x > 900) {
    _isRight = true;

    if (_isLeft) {
      leftReleased();
    }
    _isLeft = false;
  } else {
    if (_isRight) {
      rightReleased();
    }
    if (_isLeft) {
      leftReleased();
    }
    _isLeft = false;
    _isRight = false;
  }

  if (_y < 100) {
    _isUp = true;
    if (_isDown) {
      downReleased();
    }
    _isDown = false;
  } else if (_y > 900) {
    _isDown = true;

    if (_isUp) {
      upReleased();
    }
    _isUp = false;
  } else {
    if (_isDown) {
      downReleased();
    }
    if (_isUp) {
      upReleased();
    }
    _isUp = false;
    _isDown = false;
  }
}
bool JoystickHandler::isLeftReleased() {
  return _isLeftReleased;
}
bool JoystickHandler::isRightReleased() {
  return _isRightReleased;
}
bool JoystickHandler::isUpReleased() {
  return _isUpReleased;
}
bool JoystickHandler::isDownReleased() {
  return _isDownReleased;
}
bool JoystickHandler::isSWReleased() {
  return _isSWReleased;
}


void JoystickHandler::rightReleased() {
  _isLeftReleased = false;
  _isUpReleased = false;
  _isDownReleased = false;
  _isSWReleased = false;
  _isRightReleased = true;
}
void JoystickHandler::leftReleased() {
  _isRightReleased = false;
  _isUpReleased = false;
  _isDownReleased = false;
  _isSWReleased = false;
  _isLeftReleased = true;
}
void JoystickHandler::upReleased() {
  _isLeftReleased = false;
  _isRightReleased = false;
  _isDownReleased = false;
  _isSWReleased = false;
  _isUpReleased = true;
}
void JoystickHandler::downReleased() {
  _isLeftReleased = false;
  _isRightReleased = false;
  _isUpReleased = false;
  _isSWReleased = false;
  _isDownReleased = true;
}
void JoystickHandler::swReleased() {
  _isSW = false;
  _lastButtonPress = 0;
  _isLeftReleased = false;
  _isRightReleased = false;
  _isUpReleased = false;
  _isDownReleased = false;
  _isSWReleased = true;
  //Serial.println(F("swReleased"));
}
