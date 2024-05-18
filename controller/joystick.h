#ifndef JoyStick_h
#define JoyStick_h
#include "Arduino.h"

struct JoystickState {
  bool isLeftReleased;
  bool isRightReleased;
  bool isUpReleased;
  bool isDownReleased;
  bool isSWReleased;
};

class JoystickHandler {
public:
  JoystickHandler();
  JoystickHandler(uint8_t pinX, uint8_t pinY, uint8_t pinSW);
  void setup(JoystickState* state);
  void loop(JoystickState* state);
private:
  uint8_t _pinX;
  uint8_t _pinY;
  uint8_t _pinSW;

  bool _isLeft;
  bool _isRight;
  bool _isUp;
  bool _isDown;
  bool _isSW;

  unsigned long _lastButtonPress;

  void rightReleased(JoystickState* state);
  void leftReleased(JoystickState* state);
  void upReleased(JoystickState* state);
  void downReleased(JoystickState* state);
  void swReleased(JoystickState* state);
};


#endif