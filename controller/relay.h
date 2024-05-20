#ifndef Relay_h
#define Relay_h

#include "controlpinmap.h"

class RelayHandler {
public:
  RelayHandler();
  RelayHandler(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6);
  void setup();
  void start(ControlPinMapStruct* pinMap);
  void stop(ControlPinMapStruct* pinMap);
  void toSpeed(ControlPinMapStruct* pinMap, uint8_t speed);
  void pinTest(ControlPinMapStruct* pinMap, uint8_t pinNo);
private:
  uint8_t currentSpeed = 0;
  bool isRunning = false;
  int _pin1 = 0;
  int _pin2 = 0;
  int _pin3 = 0;
  int _pin4 = 0;
  int _pin5 = 0;
  int _pin6 = 0;
  void sendSignal(ControlPinMapStruct* pinMap, uint8_t pinNo);
};

#endif