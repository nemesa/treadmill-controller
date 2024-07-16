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
    Serial.println(F("get5KTraining"));
    char* result = "___________________";
    Serial.println(result);
    for (int i = 0; i < 19; i++) {
      result[i] = (char)32;  //SPACE
    }
    Serial.println(result);
    if (week == 1 || week == 2) {
      //"2W|[5|1R|2W]"
      result[0] = '2';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '5';
      result[5] = '|';
      result[6] = '1';
      result[7] = 'R';
      result[8] = '|';
      result[9] = '2';
      result[10] = 'W';
      result[11] = ']';
    } else if (week == 3 || week == 4) {
      //"2W|[8|1R|1W]|1W"
      result[0] = '2';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '8';
      result[5] = '|';
      result[6] = '1';
      result[7] = 'R';
      result[8] = '|';
      result[9] = '1';
      result[10] = 'W';
      result[11] = ']';
      result[12] = '|';
      result[13] = '1';
      result[14] = 'W';
    } else if (week == 5) {
      //3W|[4|2R|2W]|1W"
      result[0] = '3';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '4';
      result[5] = '|';
      result[6] = '2';
      result[7] = 'R';
      result[8] = '|';
      result[9] = '2';
      result[10] = 'W';
      result[11] = ']';
      result[12] = '|';
      result[13] = '1';
      result[14] = 'W';

    } else if (week == 6) {
      //"3W|[5|2R|1W]|1W"
      result[0] = '3';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '5';
      result[5] = '|';
      result[6] = '2';
      result[7] = 'R';
      result[8] = '|';
      result[9] = '1';
      result[10] = 'W';
      result[11] = ']';
      result[12] = '|';
      result[13] = '1';
      result[14] = 'W';
    } else if (week == 7) {
      //"4W|[2|2R|1W|3R|2W]"
      result[0] = '4';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '2';
      result[5] = '|';
      result[6] = '2';
      result[7] = 'R';
      result[8] = '|';
      result[9] = '1';
      result[10] = 'W';
      result[11] = '|';
      result[12] = '3';
      result[13] = 'R';
      result[14] = '|';
      result[15] = '2';
      result[16] = 'W';
      result[17] = ']';
    } else if (week == 8) {
      //"4W|[3|3R|2W]|3W"
      result[0] = '4';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '3';
      result[5] = '|';
      result[6] = '3';
      result[7] = 'R';
      result[8] = '|';
      result[9] = '2';
      result[10] = 'W';
      result[11] = ']';
      result[12] = '|';
      result[13] = '3';
      result[14] = 'W';
    } else if (week == 9) {
      //"4W|[4|3R|1W]|3W"
      result[0] = '4';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '4';
      result[5] = '|';
      result[6] = '3';
      result[7] = 'R';
      result[8] = '|';
      result[9] = '1';
      result[10] = 'W';
      result[11] = ']';
      result[12] = '|';
      result[13] = '3';
      result[14] = 'W';
    } else if (week == 10) {
      //"5W|[3|4R|2W]|2W"
      result[0] = '5';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '3';
      result[5] = '|';
      result[6] = '4';
      result[7] = 'R';
      result[8] = '|';
      result[9] = '2';
      result[10] = 'W';
      result[11] = ']';
      result[12] = '|';
      result[13] = '2';
      result[14] = 'W';
    } else if (week == 11) {
      //"5W|[2|5R|2W]|3R|4W"
      result[0] = '5';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '2';
      result[5] = '|';
      result[6] = '5';
      result[7] = 'R';
      result[8] = '|';
      result[9] = '2';
      result[10] = 'W';
      result[11] = ']';
      result[12] = '|';
      result[13] = '3';
      result[14] = 'R';
      result[15] = '|';
      result[16] = '4';
      result[17] = 'W';
    } else if (week == 12) {
      //"5W|[2|7R|2W]|2W"
      result[0] = '5';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '2';
      result[5] = '|';
      result[6] = '7';
      result[7] = 'R';
      result[8] = '|';
      result[9] = '2';
      result[10] = 'W';
      result[11] = ']';
      result[12] = '|';
      result[13] = '2';
      result[14] = 'W';
    } else if (week == 13) {
      //"5W|10R|2W|5R|5W"
      result[0] = '5';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '1';
      result[4] = '0';
      result[5] = 'R';
      result[6] = '|';
      result[7] = '2';
      result[8] = 'W';
      result[9] = '|';
      result[10] = '5';
      result[11] = 'R';
      result[12] = '|';
      result[13] = '5';
      result[14] = 'W';
    } else if (week == 14) {
      //"5W|15R|6W"
      result[0] = '5';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '1';
      result[4] = '5';
      result[5] = 'R';
      result[6] = '|';
      result[7] = '6';
      result[8] = 'W';
    } else if (week == 15) {
      //"5W|[4|5R|1W]|2W"
      result[0] = '5';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '4';
      result[5] = '|';
      result[6] = '5';
      result[7] = 'R';
      result[8] = '|';
      result[9] = '1';
      result[10] = 'W';
      result[11] = ']';
      result[12] = '|';
      result[13] = '2';
      result[14] = 'W';
    } else if (week == 16) {
      //"5W|[3|6R|1W]|4W"
      result[0] = '5';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '3';
      result[5] = '|';
      result[6] = '6';
      result[7] = 'R';
      result[8] = '|';
      result[9] = '1';
      result[10] = 'W';
      result[11] = ']';
      result[12] = '|';
      result[13] = '4';
      result[14] = 'W';
    } else if (week == 17) {
      //"5W|[3|7R|2W]|4W"
      result[0] = '5';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '3';
      result[5] = '|';
      result[6] = '7';
      result[7] = 'R';
      result[8] = '|';
      result[9] = '2';
      result[10] = 'W';
      result[11] = ']';
      result[12] = '|';
      result[13] = '4';
      result[14] = 'W';
    } else if (week == 18) {
      //"5W|10R|2W|12R|4W"
      result[0] = '5';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '1';
      result[4] = '0';
      result[5] = 'R';
      result[6] = '|';
      result[7] = '2';
      result[8] = 'W';
      result[9] = '|';
      result[10] = '1';
      result[11] = '2';
      result[12] = 'R';
      result[13] = '|';
      result[14] = '4';
      result[15] = 'W';
    } else if (week == 19) {
      //"5W|[3|9R|1W]"
      result[0] = '5';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '3';
      result[5] = '|';
      result[6] = '9';
      result[7] = 'R';
      result[8] = '|';
      result[9] = '1';
      result[10] = 'W';
      result[11] = ']';
    } else if (week == 20) {
      //"5W|15R|2W|[2|5R|2W]"
      result[0] = '5';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '1';
      result[4] = '5';
      result[5] = 'R';
      result[6] = '|';
      result[7] = '2';
      result[8] = 'W';
      result[9] = '|';
      result[10] = '[';
      result[11] = '2';
      result[12] = '|';
      result[13] = '5';
      result[14] = 'R';
      result[15] = '|';
      result[16] = '2';
      result[17] = 'W';
      result[18] = ']';
    } else if (week == 21) {
      //"5W|[3|9R|2W]"
      result[0] = '5';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '3';
      result[5] = '|';
      result[6] = '9';
      result[7] = 'R';
      result[8] = '|';
      result[9] = '2';
      result[10] = 'W';
      result[11] = ']';
    } else if (week == 22) {
      //"5W|[3|12R|2W]|4R|4W"
      result[0] = '5';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '3';
      result[5] = '|';
      result[6] = '1';
      result[7] = '2';
      result[8] = 'R';
      result[9] = '|';
      result[10] = '2';
      result[11] = 'W';
      result[12] = ']';
      result[13] = '|';
      result[14] = '4';
      result[15] = 'R';
      result[16] = '|';
      result[17] = '4';
      result[18] = 'W';
    } else if (week == 23) {
      //"5W|[3|14R|2W]|2W"
      result[0] = '5';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '[';
      result[4] = '3';
      result[5] = '|';
      result[6] = '1';
      result[7] = '4';
      result[8] = 'R';
      result[9] = '|';
      result[10] = '2';
      result[11] = 'W';
      result[12] = ']';
      result[13] = '|';
      result[14] = '2';
      result[15] = 'W';
    } else if (week == 24) {
      //"5W|18R|2W|10R|4W"
      result[0] = '5';
      result[1] = 'W';
      result[2] = '|';
      result[3] = '1';
      result[4] = '8';
      result[5] = 'R';
      result[6] = '|';
      result[7] = '2';
      result[8] = 'W';
      result[9] = '|';
      result[10] = '1';
      result[11] = '0';
      result[12] = 'R';
      result[13] = '|';
      result[14] = '4';
      result[15] = 'W';
    } else {
      result = "";
    }
    Serial.println(result);
    return result;
  }

  char* otherName(uint8_t id) {
    char* a = "30 Min Walk";
    char* b = "1 Hour 15 Min Walk";
    if (id == 25) {
      a[0] = '3';
      a[1] = '0';
      return a;
    } else if (id == 26) {
      a[0] = '4';
      a[1] = '5';
      return a;
    } else if (id == 27) {
      return "1 Hour Walk";
    } else if (id == 28) {
      b[7] = '1';
      b[8] = '5';
      return b;
    } else if (id == 29) {
      b[7] = '3';
      b[8] = '0';
      return b;
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