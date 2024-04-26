#include "HardwareSerial.h"

#include "Arduino.h"
#include "workoutdata.h"

class WorkoutHandler {
public:
  void setup() {
    Serial.println("WorkoutHandler-setup");
    for (uint8_t i = 0; i <= 23; i++) {
      struct WorkoutDataStruct workout;
      uint8_t no = i + 1;
      String name = String("5KM - week ") + String(no);
      int len = name.length();
      char nameBuffer[len + 1];
      name.toCharArray(nameBuffer, len + 1);
      workout.id = no;
      workout.name = nameBuffer;
      
      w_5k[i] = workout;
    }
  }
  WorkoutDataStruct getById(uint8_t id) {
    Serial.println("WorkoutHandler-getById " + String(id));

    if (id < 25) {
      WorkoutDataStruct found = w_5k[id - 1];
      Serial.println(found.id);
      Serial.println(found.name);
      return found;
    }
  }

private:
  WorkoutDataStruct w_5k[23];
};