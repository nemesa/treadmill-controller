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
    workout = user.lastSelection;   
    
    setMenu(0, -1);
    //setMenu(1, 2);
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
    } else if (menu == 1 && subMenu == 2) {
      setMenu(4, user.lastSelection);
    } else if (menu == 4) {
      user.lastSelection = subMenu;
      eh.writeUserData(user);
      setMenu(6, -1);  // TODO: should start workout here
    }
  }

private:
  int menu = -1;
  int subMenu = -1;
  int workout = -1;
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
        dh.mainSmallLine2("");
      } else if (subMenu == 3) {
        dh.mainSmallLine1("Run Speed:");
        dh.mainSmallLine2("");
      }
    } else if (menu = 6) {
      dh.main("Workout!");
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
    /*Serial.print(F("setMenu "));
    Serial.print(newMenu);
    Serial.print(F(" "));
    Serial.println(newSubMenu);*/
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