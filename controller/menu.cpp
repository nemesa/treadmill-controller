#include "Arduino.h"
#include "display.cpp"
#include "eeprom.cpp"
#include "workout.cpp"

class MenuHandler {
public:

  void setup() {
    Serial.println("MenuHandler-setup");
    dh.setup();
    eh.setup();
    wh.setup();

    user = eh.getLastSelectedUser();

    //startScreen();
    workoutScreen();
  }
  void down() {
    if (isStartScreen) {
      startScreenDown();
    }
    if (isWorkoutScreen) {
      workoutScreenDown();
    }
  }
  void up() {
    if (isStartScreen) {
      startScreenUp();
    }
    if (isWorkoutScreen) {
      workoutScreenUp();
    }
  }
  void left() {
    if (isWorkoutScreen) {
      workoutScreenLeft();
    }
  }
  void right() {
    if (isWorkoutScreen) {
      workoutScreenRight();
    }
  }
  void select() {
    if (isStartScreen) {
      startScreenSelect();
    }
    if (isWorkoutScreen) {
      workoutScreenSelect();
    }
  }

private:
  void startScreen() {
    isStartScreen = true;
    isWorkoutScreen = false;
    dh.cleanAll();
    dh.navigationOptions(true, false, true, false);
    dh.header("Welcome!");
    dh.main(user.name);
  }
  void startScreenDown() {
    uint8_t num = user.num + 1;
    if (num > 4) {
      num = 1;
    }
    user = eh.readUser(num);
    dh.main(user.name);
  }
  void startScreenUp() {
    uint8_t num = user.num - 1;
    if (num == 0) {
      num = 4;
    }
    user = eh.readUser(num);
    dh.main(user.name);
  }
  void startScreenSelect() {
    eh.setLastUser(user.num);
    workoutScreen();
  }
  void workoutScreen() {
    isStartScreen = false;
    isWorkoutScreen = true;
    dh.cleanAll();
    dh.navigationOptions(true, true, true, true);
    dh.header("Select Workout!");
    dh.mainSmallLine1("Start Workout:");
    String lastWorkoutName = wh.getNameById(user.lastSelection);
    
    dh.mainSmallLine2Str(lastWorkoutName);
  }
  void workoutScreenDown() {
  }
  void workoutScreenUp() {
  }
  void workoutScreenSelect() {
  }
  void workoutScreenLeft() {
    startScreen();
  }
  void workoutScreenRight() {
  }
  bool isStartScreen;
  bool isWorkoutScreen;
  UserDataStruct user;
  DisplayHandler dh;
  EEPROMHandler eh;
  WorkoutHandler wh;
};