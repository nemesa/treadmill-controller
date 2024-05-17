//I2C pins:
//SCL -> A5
//SDA -> A4
#include "display.cpp"

#include <SoftwareSerial.h>

SoftwareSerial sserial(10, 11);  // receive pin=10, transmit pin=11
#define messageBufferSize 200
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
          messageRecived(messageIndex, message);
          messageIndex = 0;
        } else {
          messageBuffer[messageIndex] = (char)incomingByte;
          messageIndex++;
        }
      }
    }
  }
}

void messageRecived(short length, char* message) {
  Serial.print(length);
  Serial.print(F("- "));
  Serial.println(message);
  char commandType = 0;
  short commandLength = -1;
  char commandBuffer[messageBufferSize];
  bool atCommandSeparator = false;

  for (short i = 0; i < length; i++) {
    char m = message[i];

    if (m == '+') {
      doCommand(commandType, commandLength - 1, commandBuffer);
      commandLength = -1;
      commandType = "";
    } else if (m == '#') {
      commandLength++;
    } else {
      if (commandLength == -1) {
        commandType = m;
      } else {
        commandBuffer[commandLength - 1] = m;
      }
      commandLength++;
    }
  }
  Serial.println(F("Done receive"));
}

void doCommand(char type, short cLength, char* commandBuffer) {
  //Serial.print(F("doCommand - "));
  //Serial.print(type);
  if (type == 'C') {
    //Serial.println();
    dh.cleanAll();
  } else {
    // Serial.print(F(" - "));
    // Serial.print(cLength);
    // Serial.print(F(" - "));
    char commandMessage[cLength];
    commandMessage[cLength] = 0;  //set the last to hold the required the null termination character

    for (short i = 0; i < cLength; i++) {
      commandMessage[i] = commandBuffer[i];
    }
    // Serial.print(commandMessage);
    // Serial.println();

    if (type == 'H') {
      dh.header(commandMessage);
    }
    if (type == 'M') {
      dh.main(commandMessage);
    }
    if (type == 'S') {
      dh.mainSmallLine1(commandMessage);
    }
    if (type == 's') {
      dh.mainSmallLine2(commandMessage);
    }
    if (type == 'M') {
      dh.main(commandMessage);
    }
    if (type == 'N') {
      dh.navigationOptions(
        commandMessage[0] == 'T',
        commandMessage[1] == 'T',
        commandMessage[2] == 'T',
        commandMessage[3] == 'T');
    }
  }
}
