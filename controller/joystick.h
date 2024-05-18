#ifndef JoyStick_h
#define JoyStick_h
#include "Arduino.h"

class JoystickHandler {
public:
  JoystickHandler();
  JoystickHandler(uint8_t pinX, uint8_t pinY, uint8_t pinSW);
  void setup();
  void loop();
  bool isLeftReleased();
  bool isRightReleased();
  bool isUpReleased();
  bool isDownReleased();
  bool isSWReleased();
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
  void rightReleased();
  void leftReleased();
  void upReleased();
  void downReleased();
  void swReleased();
};

#endif