#include "HardwareSerial.h"

#include "Arduino.h"

class WorkoutHandler {
public:
  void setup() {
    Serial.println(F("WorkoutHandler-setup"));
  }

  char* getNameById(uint8_t id) {
    if (id < 25) {
      return get5KTrainingName(id);
    }
    return otherName(id);
  }

  char* getById(uint8_t id) {
    if (id < 25) {
      return get5KTraining(id);
    }
    return other(id);
  }

  void getTimersById(short* output, uint8_t id) {
    char* details = getById(id);

    //Serial.println(details);

    short multiplerItems[] = { 0, 0, 0, 0, 0 };
    bool inMultiplier = false;
    uint8_t outIndex = 0;
    uint8_t multiplerIndex = 0;
    uint8_t numericCounter = 0;
    uint8_t multiplier = 0;
    for (uint8_t i = 0; i < strlen(details); i++) {
      uint8_t charValue = (uint8_t)details[i];
      if (48 <= charValue && charValue <= 57) {  //between 0 and 9
        uint8_t numValue = charValue - 48;
        numericCounter++;
        if (inMultiplier) {
          if (numericCounter > 1) {
            multiplerItems[multiplerIndex] = multiplerItems[multiplerIndex] * 10;
            multiplerItems[multiplerIndex] += numValue;
          } else {
            multiplerItems[multiplerIndex] = numValue;
          }
        } else {
          if (numericCounter > 1) {
            output[outIndex] = output[outIndex] * 10;
            output[outIndex] += numValue;
          } else {
            output[outIndex] = numValue;
          }
        }
      } else if (charValue == 87) {  // W
        numericCounter = 0;
      } else if (charValue == 82) {  // R
        numericCounter = 0;
        if (inMultiplier) {
          multiplerItems[multiplerIndex] = -1 * multiplerItems[multiplerIndex];
        } else {
          output[outIndex] = -1 * output[outIndex];
        }
      } else if (charValue == 91) {  // [
        inMultiplier = true;
        numericCounter = 0;
      } else if (charValue == 93) {  // ]
        inMultiplier = false;
        numericCounter = 0;
        for (uint8_t i = 0; i < multiplerItems[0]; i++) {
          for (uint8_t j = 1; j < 5; j++) {
            if (multiplerItems[j] != 0) {
              output[outIndex] = multiplerItems[j];
              outIndex++;
            }
          }
        }
        outIndex--;

      } else if (charValue == 124) {  // |
        if (inMultiplier == true) {
          multiplerIndex++;
        } else {
          outIndex++;
        }
        numericCounter = 0;
      }
    }
    for (uint8_t i = 0; i < 20; i++) {
      output[i] = output[i] * 60;
    }
  }

private:
  char* get5KTrainingName(uint8_t week) {
    char* name = "5KM - week   ";
    if (week < 10) {
      name[11] = (char)(48 + week);
      name[12] = ' ';
    } else {
      name[11] = (char)(48 + (week / 10));
      if (week % 10 == 0) {
        name[12] = '0';
      } else {
        name[12] = (char)(48 + (week % 10));
      }
    }
    return name;
  }

  char* get5KTraining(uint8_t week) {
    char* result;
    if (week == 1 || week == 2) {
      result = "2W|[5|1R|1W]";
    } else if (week == 3 || week == 4) {
      result = "2W|[8|1R|1W]|1W";
    } else if (week == 4) {
      result = "2W|[8|1R|1W]|1W";
    } else if (week == 5) {
      result = "3W|[4|2R|2W]|1W";
    } else if (week == 6) {
      result = "3W|[5|2R|1W]|1W";
    } else if (week == 7) {
      result = "4W|[2|2R|1W|3R|2W]";
    } else if (week == 8) {
      result = "4W|[3|3R|2W]|3W";
    } else if (week == 9) {
      result = "4W|[4|3R|1W]|3W";
    } else if (week == 10) {
      result = "5W|[3|4R|2W]|2W";
    } else if (week == 11) {
      result = "5W|[2|5R|2W]|3R|4W";
    } else if (week == 12) {
      result = "5W|[2|7R|2W]|2W";
    } else if (week == 13) {
      result = "5W|10R|2W|5R|5W";
    } else if (week == 14) {
      result = "5W|15R|6W";
    } else if (week == 15) {
      result = "5W|[4|5R|1W]|2W";
    } else if (week == 16) {
      result = "5W|[3|6R|1W]|4W";
    } else if (week == 17) {
      result = "5W|[3|7R|2W]|4W";
    } else if (week == 18) {
      result = "5W|10R|2W|12R|4W";
    } else if (week == 19) {
      result = "5W|[3|9R|1W]";
    } else if (week == 20) {
      result = "5W|15R|2W|[2|5R|2W]";
    } else if (week == 21) {
      result = "5W|[3|9R|2W]";
    } else if (week == 22) {
      result = "5W|[3|12R|2W]|4R|4W";
    } else if (week == 23) {
      result = "5W|[3|14R|2W]|2W";
    } else if (week == 24) {
      result = "5W|18R|2W|10R|4W";
    } else {
      result = "";
    }
    return result;
  }

  char* otherName(uint8_t id) {
    if (id == 25) {
      return "30 Min Walk";
    } else if (id == 26) {
      return "45 Min Walk";
    } else if (id == 27) {
      return "1 Hour Walk";
    } else if (id == 28) {
      return "1 Hour 15 Min Walk";
    } else if (id == 29) {
      return "1 Hour 30 Min Walk";
    } else {
      return "INVALID";
    }
  }
  char* other(uint8_t id) {
    char* result = "00W";
    if (id == 25) {
      result[0] = '3';
      result[1] = '0';
    } else if (id == 26) {
      result[0] = '4';
      result[1] = '5';
    } else if (id == 27) {
      result[0] = '6';
      result[1] = '0';
    } else if (id == 28) {
      result[0] = '7';
      result[1] = '5';
    } else if (id == 29) {
      result[0] = '9';
      result[1] = '0';
    } else {
      result = "";
    }
    return result;
  }
};