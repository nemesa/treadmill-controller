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
    workout = user.lastSelection;
    //setMenu(0, -1);
    setMenu(1, 1);
  }
  void down() {
    if (menu == 0) {
      readNextUser();
      dh.main(user.name);
    }
    if (menu == 1) {
      subMenu = subMenu + 1;
      if (subMenu == 4) {
        subMenu = 1;
      }
      setMenu(1, subMenu);
    }
  }
  void up() {
    if (menu == 0) {
      readPrevUser();
      dh.main(user.name);
    }
    if (menu == 1) {
      subMenu = subMenu - 1;
      if (subMenu == 0) {
        subMenu = 3;
      }
      setMenu(1, subMenu);
    }
  }
  void left() {
    if (menu == 1) {
      setMenu(0, -1);
    }
  }
  void right() {
    if (menu == 1) {
      setMenu(3, -1);
    }
  }
  void select() {
    if (menu == 0) {
      eh.setLastUser(user.num);
      setMenu(1, 1);
    }
  }

private:
  int menu = -1;
  int subMenu = -1;
  int workout = -1;
  void render() {
    if (menu == 0) {
      dh.navigationOptions(true, false, true, false);
      dh.header("Welcome!");
      dh.main(user.name);
    } else if (menu == 1) {
      dh.navigationOptions(true, true, true, true);
      dh.header("Select Workout!");
      if (subMenu == 1) {
        dh.mainSmallLine1("Start Last Selected:");
        dh.mainSmallLine2(wh.getNameById(user.lastSelection));
      } else if (subMenu == 2) {
        dh.mainSmallLine1("Other Workouts");
        dh.mainSmallLine2("");
      } else if (subMenu == 3) {
        dh.mainSmallLine1("User Settings");
        dh.mainSmallLine2("");
      }
    } else if (menu == 3) {
      /*dh.header("Last Workout Details:");
      dh.navigationOptions(false, true, false, false);
      dh.mainSmallLine1(wh.getNameById(user.lastSelection));
      dh.mainSmallLine2(wh.getById(user.lastSelection));*/
    }
  };
  void readNextUser() {
    uint8_t num = user.num + 1;
    if (num > 4) {
      num = 1;
    }
    user = eh.readUser(num);
  };
  void readPrevUser() {
    uint8_t num = user.num - 1;
    if (num == 0) {
      num = 4;
    }
    user = eh.readUser(num);
  }
  void setMenu(int newMenu, int newSubMenu) {
    if (menu != newMenu) {
      dh.cleanAll();
    }
    menu = newMenu;
    subMenu = newSubMenu;
    render();
  };
  UserDataStruct user;
  DisplayHandler dh;
  EEPROMHandler eh;
  WorkoutHandler wh;
};

/*
class MenuHandler {
public:

  void setup() {
    Serial.println("MenuHandler-setup");
    dh.setup();
    eh.setup();
    wh.setup();

    user = eh.getLastSelectedUser();

    subWorkoutScreen = 0;
    isStartScreen = false;
    isWorkoutScreen = false;
    otherWorkoutId = 1;
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
    subWorkoutScreen = 0;
    dh.cleanAll();
    dh.navigationOptions(true, true, true, true);
    dh.header("Select Workout!");
    workoutStartLastScreen();
  }
  void workoutDetailsScreen(uint8_t id) {
    subWorkoutScreen = 1;
    dh.cleanAll();
    dh.navigationOptions(false, true, false, false);
    dh.header("Workout Details:");
    dh.mainSmallLine1(wh.getNameById(id));
    dh.mainSmallLine2(wh.getById(id));
  }
  void workoutStartLastScreen() {
    subWorkoutScreen = 0;
    dh.mainSmallLine1("Start Workout:");
    dh.mainSmallLine2(wh.getNameById(user.lastSelection));
  }
  void workoutOtherScreen() {
    subWorkoutScreen = 2;
    dh.mainSmallLine1("Other Workouts");
    dh.mainSmallLine2("");
  }
  void userSettingsScreen() {
    subWorkoutScreen = 3;
    dh.mainSmallLine1("User Settings");
    dh.mainSmallLine2("");
  }
  void workoutScreenDown() {
    if (subWorkoutScreen == 0) {
      workoutOtherScreen();
    } else if (subWorkoutScreen == 2) {
      userSettingsScreen();
    } else if (subWorkoutScreen == 3) {
      workoutStartLastScreen();
    }
  }
  void workoutScreenUp() {
    if (subWorkoutScreen == 0) {
      userSettingsScreen();
    } else if (subWorkoutScreen == 2) {
      workoutStartLastScreen();
    } else if (subWorkoutScreen == 3) {
      workoutOtherScreen();
    }
  }
  void workoutScreenSelect() {
  }
  void workoutScreenLeft() {
    if (subWorkoutScreen == 0) {
      startScreen();
    }
    if (subWorkoutScreen == 1) {
      workoutScreen();
    }
  }
  void workoutScreenRight() {
    if (subWorkoutScreen == 0) {
      workoutDetailsScreen(user.lastSelection);
    }
  }
  bool isStartScreen;
  bool isWorkoutScreen;
  int subWorkoutScreen;
  int otherWorkoutId;
  UserDataStruct user;
  DisplayHandler dh;
  EEPROMHandler eh;
  WorkoutHandler wh;
};
*/