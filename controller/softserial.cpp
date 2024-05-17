#include <SoftwareSerial.h>
#include "Arduino.h"

#define ELEMENTS(x) (sizeof(x) / sizeof(x[0]))

class SoftSerialHandler {
public:
  SoftSerialHandler() {
  }
  void setup() {
    Serial.println(F("SoftSerialHandler-setup"));
    sserial.begin(9600);
    //sserial = SoftwareSerial(10, 11);  // receive pin=10, transmit pin=11
  }
  void send(bool doClean, char* message) {
    Serial.println(F("SoftSerialHandler-send"));
    Serial.println(message);

    sserial.write("&");
    if (doClean) {
      sserial.write("C+");
    }
    sserial.write(message);
    sserial.write("$");
  }

  void send(bool doClean, char* messageA, char* messageB) {
    Serial.println(F("SoftSerialHandler-sendMultiple"));
    Serial.print(messageA);
    Serial.println(messageB);

    sserial.write("&");
    if (doClean) {
      sserial.write("C+");
    }
    sserial.write(messageA);
    sserial.write(messageB);

    sserial.write("$");
  }

  void send(bool doClean, char* messageA, char* messageB, char* messageC) {
    Serial.println(F("SoftSerialHandler-sendMultiple"));
    Serial.print(messageA);
    Serial.print(messageB);
    Serial.println(messageC);

    sserial.write("&");
    if (doClean) {
      sserial.write("C+");
    }
    sserial.write(messageA);
    sserial.write(messageB);
    sserial.write(messageC);

    sserial.write("$");
  }


  void send(bool doClean, char* messageA, char* messageB, char* messageC, char* messageD) {
    Serial.println(F("SoftSerialHandler-sendMultiple"));
    Serial.print(messageA);
    Serial.print(messageB);
    Serial.print(messageC);
    Serial.println(messageD);

    sserial.write("&");
    if (doClean) {
      sserial.write("C+");
    }
    sserial.write(messageA);
    sserial.write(messageB);
    sserial.write(messageC);
    sserial.write(messageD);

    sserial.write("$");
  }

  void send(bool doClean, char* messageA, char* messageB, char* messageC, char* messageD, char* messageE) {
    Serial.println(F("SoftSerialHandler-sendMultiple"));
    Serial.print(messageA);
    Serial.print(messageB);
    Serial.print(messageC);
    Serial.print(messageD);
    Serial.println(messageE);

    sserial.write("&");
    if (doClean) {
      sserial.write("C+");
    }
    sserial.write(messageA);
    sserial.write(messageB);
    sserial.write(messageC);
    sserial.write(messageD);
    sserial.write(messageE);

    sserial.write("$");
  }

private:
  SoftwareSerial sserial = SoftwareSerial(10, 11);
};