#include "Arduino.h"
#include "joystick.h"

JoystickHandler::JoystickHandler(uint8_t pinX, uint8_t pinY, uint8_t pinSW) {
  _pinX = pinX;
  _pinY = pinY;
  _pinSW = pinSW;
}

void JoystickHandler::setup(JoystickState* state) {
  Serial.println(F("JojoystickHandler-setup"));

  state->isLeftReleased = false;
  state->isRightReleased = false;
  state->isUpReleased = false;
  state->isDownReleased = false;
  state->isSWReleased = false;

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


void JoystickHandler::loop(JoystickState* state) {

  state->isLeftReleased = false;
  state->isRightReleased = false;
  state->isUpReleased = false;
  state->isDownReleased = false;
  state->isSWReleased = false;

  int x = analogRead(_pinX);
  int y = analogRead(_pinY);
  int sw = digitalRead(_pinSW);
/*
  Serial.print(F("JoystickHandler-loop x:"));
  Serial.print(x);
  Serial.print(F(" y:"));
  Serial.print(y);
  Serial.print(F(" sw:"));
  Serial.println(sw);*/

  if (sw== 0) {

    if (!_isSW) {
      _lastButtonPress = millis();
    }
    _isSW = true;
  } else {
    if (_isSW && _lastButtonPress + 100 < millis()) {
      swReleased(state);
    }
  }


  if (x < 100) {
    _isLeft = true;
    if (_isRight) {
      rightReleased(state);
    }
    _isRight = false;
  } else if (x > 900) {
    _isRight = true;

    if (_isLeft) {
      leftReleased(state);
    }
    _isLeft = false;
  } else {
    if (_isRight) {
      rightReleased(state);
    }
    if (_isLeft) {
      leftReleased(state);
    }
    _isLeft = false;
    _isRight = false;
  }

  if (y < 100) {
    _isUp = true;
    if (_isDown) {
      downReleased(state);
    }
    _isDown = false;
  } else if (y > 900) {
    _isDown = true;

    if (_isUp) {
      upReleased(state);
    }
    _isUp = false;
  } else {
    if (_isDown) {
      downReleased(state);
    }
    if (_isUp) {
      upReleased(state);
    }
    _isUp = false;
    _isDown = false;
  }
}

void JoystickHandler::rightReleased(JoystickState* state) {
  state->isLeftReleased = false;
  state->isUpReleased = false;
  state->isDownReleased = false;
  state->isSWReleased = false;
  state->isRightReleased = true;

  Serial.println(F("rightReleased"));
}
void JoystickHandler::leftReleased(JoystickState* state) {
  state->isRightReleased = false;
  state->isUpReleased = false;
  state->isDownReleased = false;
  state->isSWReleased = false;
  state->isLeftReleased = true;

  Serial.println(F("leftReleased"));
}
void JoystickHandler::upReleased(JoystickState* state) {
  state->isLeftReleased = false;
  state->isRightReleased = false;
  state->isDownReleased = false;
  state->isSWReleased = false;
  state->isUpReleased = true;

  Serial.println(F("upReleased"));
}
void JoystickHandler::downReleased(JoystickState* state) {
  state->isLeftReleased = false;
  state->isRightReleased = false;
  state->isUpReleased = false;
  state->isSWReleased = false;
  state->isDownReleased = true;

  Serial.println(F("downReleased"));
}
void JoystickHandler::swReleased(JoystickState* state) {
  _isSW = false;
  _lastButtonPress = 0;
  state->isLeftReleased = false;
  state->isRightReleased = false;
  state->isUpReleased = false;
  state->isDownReleased = false;
  state->isSWReleased = true;
  Serial.println(F("swReleased"));
}
