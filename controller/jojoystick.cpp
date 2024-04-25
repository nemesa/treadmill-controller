#include "Arduino.h"

class JojoystickHandler {
public:
  void setup(uint8_t pinX, uint8_t pinY, uint8_t pinSW) {
    _pinX = pinX;
    _pinY = pinY;
    Serial.println("JojoystickHandler-setup");
    pinMode(_pinX, INPUT);
    pinMode(_pinY, INPUT);
    _isLeft = false;
  }
  void loop() {

    _isLeftReleased = false;
    _isRightReleased = false;
    _isUpReleased = false;
    _isDownReleased = false;
    _x = analogRead(_pinX);
    _y = analogRead(_pinY);
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
  bool isLeftReleased(){
    return _isLeftReleased;
  }
  bool isRightReleased(){
    return _isRightReleased;
  }
  bool isUpReleased(){
    return _isUpReleased;
  }
  bool isDownReleased(){
    return _isDownReleased;
  }
private:
  bool _isLeft;
  bool _isRight;
  bool _isUp;
  bool _isDown;
  int _x;
  int _y;
  int _pinX;
  int _pinY;
  bool _isLeftReleased;
  bool _isRightReleased;
  bool _isUpReleased;
  bool _isDownReleased;

  void rightReleased() {
    _isRightReleased = true;
    Serial.println("RIGHT is released");
  }
  void leftReleased() {
    _isLeftReleased = true;
    Serial.println("LEFT is released");
  }
  void upReleased() {
    _isUpReleased = true;
    Serial.println("UP is released");
  }
  void downReleased() {
    _isDownReleased = true;
    Serial.println("DOWN is released");
  }
};