#include "Arduino.h"

class JojoystickHandler {
public:
  void setup(uint8_t pinX, uint8_t pinY, uint8_t pinSW) {
    Serial.println(F("JojoystickHandler-setup"));
    _pinX = pinX;
    _pinY = pinY;
    _pinSW = pinSW;
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
  void loop() {

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
  bool isLeftReleased() {
    return _isLeftReleased;
  }
  bool isRightReleased() {
    return _isRightReleased;
  }
  bool isUpReleased() {
    return _isUpReleased;
  }
  bool isDownReleased() {
    return _isDownReleased;
  }
  bool isSWReleased() {
    return _isSWReleased;
  }
private:
  bool _isLeft;
  bool _isRight;
  bool _isUp;
  bool _isDown;
  bool _isSW;
  int _x;
  int _y;
  int _sw;
  uint8_t _pinX;
  uint8_t _pinY;
  uint8_t _pinSW;
  bool _isLeftReleased;
  bool _isRightReleased;
  bool _isUpReleased;
  bool _isDownReleased;
  bool _isSWReleased;
  unsigned long _lastButtonPress;

  void rightReleased() {
    _isLeftReleased = false;
    _isUpReleased = false;
    _isDownReleased = false;
    _isSWReleased = false;
    _isRightReleased = true;
  }
  void leftReleased() {
    _isRightReleased = false;
    _isUpReleased = false;
    _isDownReleased = false;
    _isSWReleased = false;
    _isLeftReleased = true;
  }
  void upReleased() {
    _isLeftReleased = false;
    _isRightReleased = false;
    _isDownReleased = false;
    _isSWReleased = false;
    _isUpReleased = true;
  }
  void downReleased() {
    _isLeftReleased = false;
    _isRightReleased = false;
    _isUpReleased = false;
    _isSWReleased = false;
    _isDownReleased = true;
  }
  void swReleased() {
    _isSW = false;
    _lastButtonPress = 0;
    _isLeftReleased = false;
    _isRightReleased = false;
    _isUpReleased = false;
    _isDownReleased = false;
    _isSWReleased = true;
    //Serial.println(F("swReleased"));
  }
};