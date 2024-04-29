#include "HardwareSerial.h"

#include "Arduino.h"
#include "workoutdata.h"

class WorkoutHandler {
public:
  void setup() {
    Serial.println("WorkoutHandler-setup");
    for (int i = 0; i <= 23; i++) {
      struct WorkoutDataStruct workout;
      workout.name = "                   ";
      int no = i + 1;
      String name = String("      5KM - week ") + String(no);

      name.toCharArray(workout.name, 20);
      w_5k[i] = workout;
      Serial.println(String(i) + " " + w_5k[i].name);
    }
    Serial.println(w_5k[2].name);
  }

  WorkoutDataStruct getById(uint8_t id) {
    Serial.println("WorkoutHandler-getById " + String(id));

    if (id < 25) {
      return get5KTraining(id);
    }
  }

private:
  WorkoutDataStruct get5KTraining(uint8_t week) {
    struct WorkoutDataStruct workout;
    workout.name = "                   ";
    String name = String("      5KM - week ") + String(week);    
    name.toCharArray(workout.name, 20);
    /*
    

1-2	2W|[5|1R|1W]
3-4	2W|[8|1R|1W]|1W
5	  3W|[4|2R|2W]|1W
6	  3W|[5|2R|1W]|1W
7	  4W|[2|2R|1W|3R|2W]
8	  4W|[3|3R|2W]|3W
9	  4W|[4|3R|1W]|3W
10	5W|[3|4R|2W]|2W
11	5W|[2|5R|2W]|3R|4W
12	5W|[2|7R|2W]|2W
13	5W|10R|2W|5E|5W
14	5W|15R|6W
15	5W|[4|5R|1W]|2W
16	5W|[3|6R|1W]|4W
17	5W|[3|7R|2W]|4W
18	5W|10R|2W|12R|4W
19	5W|[3|9R|1W]
20	5W|15R|2W|[2X|5R|2W]
21	5W|[3|9R|2W]
22	5W|[3|12R|2W]|4R|4W
23	5W|[3|14R|2W]|2W
24	5W|18R|2W|10R|4W


    
    */
  }
  WorkoutDataStruct w_5k[23];
};