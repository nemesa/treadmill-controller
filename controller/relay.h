#ifndef Relay_h
#define Relay_h

class RelayHandler {
public:
  RelayHandler();
  RelayHandler(int pin);
  void setup();
  void start();
private:
  int _pin = 0;
};

#endif