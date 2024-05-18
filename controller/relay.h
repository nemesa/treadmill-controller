#ifndef Relay_h
#define Relay_h

class RelayHandler {
public:
  RelayHandler();
  RelayHandler(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6);
  void setup();
  void start();
  void stop();
  void toSpeed(uint8_t speed);
private:
  uint8_t currentSpeed = 0;
  bool isRunning = false;
  int _pin1 = 0;
  int _pin2 = 0;
  int _pin3 = 0;
  int _pin4 = 0;
  int _pin5 = 0;
  int _pin6 = 0;
};

#endif