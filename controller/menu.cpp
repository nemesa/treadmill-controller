#include "Arduino.h"
#include "display.cpp"
#include "eeprom.cpp"
#include "workout.cpp"

class MenuHandler {
public:

  void setup() {
    Serial.println(F("MenuHandler-setup"));
    dh.setup();
    eh.setup();
    wh.setup();
    user = eh.getLastSelectedUser();
    setUser(user.num);

    setMenu(0, -1);
    //setMenu(6, -1);
  }
  void down() {
    if (menu == 0) {
      readNextUser();
      dh.main(user.name);
    } else if (menu == 1) {
      subMenu = subMenu + 1;
      if (subMenu == 4) {
        subMenu = 1;
      }
      setMenu(1, subMenu);
    } else if (menu == 4) {
      subMenu = subMenu + 1;
      if (subMenu == 30) {
        subMenu = 1;
      }
      setMenu(4, subMenu);
    } else if (menu == 5 && subMenu < 10) {
      subMenu = subMenu + 1;
      if (subMenu == 4) {
        subMenu = 1;
      }
      setMenu(5, subMenu);
    } else if (menu == 5 && subMenu == 20) {
      walkSpeed = walkSpeed - 1;
      if (walkSpeed == 0) {
        walkSpeed = 1;
      }
      dh.main(getSpeed(walkSpeed));
    } else if (menu == 5 && subMenu == 30) {
      runSpeed = runSpeed - 1;
      if (runSpeed == 0) {
        runSpeed = 1;
      }
      dh.main(getSpeed(runSpeed));
    }
  }
  void up() {
    if (menu == 0) {
      readPrevUser();
      dh.main(user.name);
    } else if (menu == 1) {
      subMenu = subMenu - 1;
      if (subMenu == 0) {
        subMenu = 3;
      }
      setMenu(1, subMenu);
    } else if (menu == 4) {
      subMenu = subMenu - 1;
      if (subMenu == 0) {
        subMenu = 29;
      }
      setMenu(4, subMenu);
    } else if (menu == 5 && subMenu < 10) {
      subMenu = subMenu - 1;
      if (subMenu == 0) {
        subMenu = 3;
      }
      setMenu(5, subMenu);
    } else if (menu == 5 && subMenu == 20) {
      walkSpeed = walkSpeed + 1;
      if (walkSpeed == 161) {
        walkSpeed = 160;
      }
      dh.main(getSpeed(walkSpeed));
    } else if (menu == 5 && subMenu == 30) {
      runSpeed = runSpeed + 1;
      if (runSpeed == 161) {
        runSpeed = 160;
      }
      dh.main(getSpeed(runSpeed));
    }
  }
  void left() {
    if (menu == 1) {
      setMenu(0, -1);
    } else if (menu == 3) {
      setMenu(1, 1);
    } else if (menu == 4) {
      setMenu(1, 2);
    } else if (menu == 5) {
      setMenu(1, 3);
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
    } else if (menu == 1 && subMenu == 1) {
      setMenu(6, -1);
    } else if (menu == 1 && subMenu == 2) {
      setMenu(4, user.lastSelection);
    } else if (menu == 1 && subMenu == 3) {
      setMenu(5, 1);
    } else if (menu == 3) {
      setMenu(6, -1);
    } else if (menu == 4) {
      user.lastSelection = subMenu;
      eh.writeUserData(user);
      setMenu(6, -1);
    } else if (menu == 5) {
      if (subMenu == 1) {
      } else if (subMenu == 2) {
        setMenu(5, 20);
      } else if (subMenu == 3) {
        setMenu(5, 30);
      } else if (subMenu == 20) {
        user.walkSpeed = walkSpeed;
        eh.writeUserData(user);
        setMenu(5, 2);
      } else if (subMenu == 30) {
        user.runSpeed = runSpeed;
        eh.writeUserData(user);
        setMenu(5, 3);
      }
    } else if (menu == 6) {
      setMenu(1, 1);
    }
  }
  void timerTick() {
    if (menu == 6) {
      if (!inTimer) {
        inTimer = true;
        Serial.println(F("Timer 1"));
        dh.debug("12:09");
        inTimer = false;
      }
    }
  }

private:
  uint8_t menu = -1;
  uint8_t subMenu = -1;
  uint8_t walkSpeed = -1;
  uint8_t runSpeed = -1;
  bool inTimer = false;
  short timeTick = 0;
  void render() {
    /*Serial.print(F("render "));
    Serial.print(menu);
    Serial.print(F(" "));
    Serial.println(subMenu);*/
    if (menu == 0) {
      dh.navigationOptions(true, false, true, false);
      dh.header("Welcome!");
      dh.main(user.name);
    } else if (menu == 1) {
      dh.header("Select Workout!");
      if (subMenu == 1) {
        dh.navigationOptions(true, true, true, true);
        dh.mainSmallLine1("Start Last Selected:");
        dh.mainSmallLine2(wh.getNameById(user.lastSelection));
      } else if (subMenu == 2) {
        dh.navigationOptions(true, true, true, false);
        dh.mainSmallLine1("Other Workouts");
        dh.mainSmallLine2("");
      } else if (subMenu == 3) {
        dh.navigationOptions(true, true, true, false);
        dh.mainSmallLine1("User Settings");
        dh.mainSmallLine2("");
      }
    } else if (menu == 3) {
      dh.header("Last Workout Details:");
      dh.navigationOptions(false, true, false, false);
      dh.mainSmallLine1(wh.getNameById(user.lastSelection));
      dh.mainSmallLine2(wh.getById(user.lastSelection));
    } else if (menu == 4) {
      dh.header("Other workouts:");
      dh.navigationOptions(true, true, true, false);
      dh.mainSmallLine1(wh.getNameById(subMenu));
      dh.mainSmallLine2(wh.getById(subMenu));
    } else if (menu == 5) {
      dh.header("Settings:");
      dh.navigationOptions(true, true, true, false);
      if (subMenu == 1) {
        dh.mainSmallLine1("Name:");
        dh.mainSmallLine2(user.name);
      } else if (subMenu == 2) {
        dh.mainSmallLine1("Walk Speed:");
        dh.mainSmallLine2(getSpeed(user.walkSpeed));
      } else if (subMenu == 20) {
        dh.header("Walk Speed:");
        dh.main(getSpeed(user.walkSpeed));
      } else if (subMenu == 3) {
        dh.mainSmallLine1("Run Speed:");
        dh.mainSmallLine2(getSpeed(user.runSpeed));
      } else if (subMenu == 30) {
        dh.header("Run Speed:");
        dh.main(getSpeed(user.runSpeed));
      }
    } else if (menu = 6) {
      dh.main("12:09");
      short timers[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
      wh.getTimersById(timers, user.lastSelection);
      for (uint8_t i = 0; i < 20; i++) {
        Serial.print(timers[i]);
        Serial.print(F(", "));
      }
      Serial.println(F(""));
    }
  };
  void readNextUser() {
    uint8_t num = user.num + 1;
    if (num > 4) {
      num = 1;
    }
    setUser(num);
  };
  void readPrevUser() {
    uint8_t num = user.num - 1;
    if (num == 0) {
      num = 4;
    }
    setUser(num);
  }
  void setMenu(int newMenu, int newSubMenu) {
    /*Serial.print(F("setMenu "));
    Serial.print(newMenu);
    Serial.print(F(" "));
    Serial.println(newSubMenu);*/
    if (menu != newMenu) {
      dh.cleanAll();
    }
    menu = newMenu;
    subMenu = newSubMenu;
    inTimer = false;
    timeTick = 0;
    render();
  };
  char* getSpeed(uint8_t speed) {
    Serial.print(F("getSpeed "));
    Serial.println(speed);

    char* result = "00.0";
    if (speed < 100) {
      result[0] = ' ';
    }
    if (speed < 10) {
      result[3] = (char)(48 + speed);
    } else {
      if (speed > 100) {
        result[0] = (char)(48 + speed / 100);
        result[1] = (char)(48 + ((speed - 100) / 10));
        result[3] = (char)(48 + ((speed - 100) % 10));
      } else {
        result[1] = (char)(48 + speed / 10);
        result[3] = (char)(48 + speed % 10);
      }
    }
    return result;
  }
  void setUser(uint8_t num) {
    user = eh.readUser(num);
    walkSpeed = user.walkSpeed;
    runSpeed = user.runSpeed;
  }
  UserDataStruct user;
  DisplayHandler dh;
  EEPROMHandler eh;
  WorkoutHandler wh;
  //short workoutTimers[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  short workoutTimers[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
};