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
    //Serial.println("JojoystickHandler-loop");
    _x = analogRead(_pinX);
    _y = analogRead(_pinY);
    //Serial.print("x: ");
    //Serial.print(_x);
    //Serial.print(" y: ");
    //Serial.println(_y);
    if (_x < 200) {
      _isLeft = true;
      if (_isRight) {
        rightReleased();
      }
      _isRight = false;
    } else if (_x > 800) {
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

    if (_y < 200) {
      _isUp = true;
      if (_isDown) {
        downReleased();
      }
      _isDown = false;
    } else if (_y > 800) {
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
private:
  bool _isLeft;
  bool _isRight;
  bool _isUp;
  bool _isDown;
  int _x;
  int _y;
  int _pinX;
  int _pinY;
  void rightReleased() {
    Serial.println("RIGHT is released");
  }
  void leftReleased() {
    Serial.println("LEFT is released");
  }
  void upReleased() {
    Serial.println("UP is released");
  }
  void downReleased() {
    Serial.println("DOWN is released");
  }
};