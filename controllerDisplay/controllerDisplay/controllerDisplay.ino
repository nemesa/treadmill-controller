//I2C pins:
//SCL -> A5
//SDA -> A4
#include "display.cpp"

#include <SoftwareSerial.h>

SoftwareSerial sserial(10, 11);  // receive pin=10, transmit pin=11
#define messageBufferSize 50
char messageBuffer[messageBufferSize];
short messageIndex = 0;
DisplayHandler dh;

void setup() {
  Serial.begin(9600);
  sserial.begin(9600);  // start serial connection
  Serial.println(F("setup"));
  dh.setup();
  for (short i = 0; i < messageBufferSize; i++) {
    messageBuffer[i] = 0;
  }
}


void loop() {
  if (sserial.available() > 0) {
    while (sserial.available() > 0) {

      byte incomingByte = 0;
      incomingByte = sserial.read();
      if (incomingByte != -1) {
        if (incomingByte == 38) {  //'&'
          messageIndex = 0;
        } else if (incomingByte == 36) {  //'$'
          char message[messageIndex];
          for (short i = 0; i < messageBufferSize; i++) {
            if (i <= messageIndex) {
              message[i] = messageBuffer[i];
            }
            messageBuffer[i] = 0;
          }
          messageRecived(message);
          messageIndex = 0;
        } else {
          messageBuffer[messageIndex] = (char)incomingByte;
          messageIndex++;
        }
      }
    }
  }
}

void messageRecived(char* message) {
  Serial.println(message);
  dh.cleanAll();
  dh.debug(message);
  Serial.println("Done receive");
}
