#include "HardwareSerial.h"

#include "Arduino.h"

class WorkoutHandler {
public:
  void setup() {
    Serial.println("WorkoutHandler-setup");
  }

  char* getNameById(uint8_t id) {
    if (id < 25) {
      return get5KTrainingName(10);
    }
  }

  char* getById(uint8_t id) {
    if (id < 10) {
      return get5KTraining1(id);
    } /*
    if (id < 19) {
      return get5KTraining2(id);
    }
    if (id < 25) {
      return get5KTraining3(id);
    }*/
  }

private:
  char* get5KTrainingName(uint8_t week) {
    Serial.print("get5KTrainingName ");
    Serial.println(week);
    char* name = "5KM - week   ";
    if (week < 10) {
      name[11] = (char)(48 + week);
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

  char* get5KTraining1(uint8_t week) {
    if (week == 1 || week == 2) {
      return "2W|[5|1R|1W]";
    } /*else if (week == 3 || week == 4) {
      return "2W|[8|1R|1W]|1W";
    } else if (week == 4) {
      return "2W|[8|1R|1W]|1W";
    } else if (week == 5) {
      return "3W|[4|2R|2W]|1W";
    } else if (week == 6) {
      return "3W|[5|2R|1W]|1W";
    } else if (week == 7) {
      return "4W|[2|2R|1W|3R|2W]";
    } else if (week == 8) {
      return "4W|[3|3R|2W]|3W";
    } else if (week == 9) {
      return "4W|[4|3R|1W]|3W";
    }*/
    return "";
  }

  char* get5KTraining2(uint8_t week) {

    if (week == 10) {
      return "5W|[3|4R|2W]|2W";
    } else if (week == 11) {
      return "5W|[2|5R|2W]|3R|4W";
    } else if (week == 12) {
      return "5W|[2|7R|2W]|2W";
    } else if (week == 13) {
      return "5W|10R|2W|5E|5W";
    } else if (week == 14) {
      return "5W|15R|6W";
    } else if (week == 15) {
      return "5W|[4|5R|1W]|2W";
    } else if (week == 16) {
      return "5W|[3|6R|1W]|4W";
    } else if (week == 17) {
      return "5W|[3|7R|2W]|4W";
    }
    return "";
  }
  char* get5KTraining3(uint8_t week) {
    if (week == 18) {
      return "5W|10R|2W|12R|4W";
    } else if (week == 19) {
      return "5W|[3|9R|1W]";
    } else if (week == 20) {
      return "5W|15R|2W|[2X|5R|2W]";
    } else if (week == 21) {
      return "5W|[3|9R|2W]";
    } else if (week == 22) {
      return "5W|[3|12R|2W]|4R|4W";
    } else if (week == 23) {
      return "5W|[3|14R|2W]|2W";
    } else if (week == 24) {
      return "5W|18R|2W|10R|4W";
    }
    return "";
  }
};