#include "Arduino.h"
#include "eeprom.cpp"
#include "workout.cpp"
#include "softserial.cpp"

class MenuHandler {
public:

  void setup(int ssRx, int ssTx) {
    Serial.println(F("MenuHandler-setup"));
    eh.setup();
    wh.setup();
    ssh.setup(ssRx,ssTx);
    user = eh.getLastSelectedUser();
    setUser(user.num);

    //setMenu(0, -1);
    setMenu(1, 1);
    //setMenu(6, -1);
  }
  void down() {
    if (menu == 0) {
      readNextUser();
      ssh.send(false, "M#", user.name, "+");

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
      ssh.send(false, "M#", getSpeed(walkSpeed), "+");
    } else if (menu == 5 && subMenu == 30) {
      runSpeed = runSpeed - 1;
      if (runSpeed == 0) {
        runSpeed = 1;
      }
      ssh.send(false, "M#", getSpeed(runSpeed), "+");
    }
  }
  void up() {
    if (menu == 0) {
      readPrevUser();
      ssh.send(false, "M#", user.name, "+");
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
      ssh.send(false, "M#", getSpeed(walkSpeed), "+");
    } else if (menu == 5 && subMenu == 30) {
      runSpeed = runSpeed + 1;
      if (runSpeed == 161) {
        runSpeed = 160;
      }
      ssh.send(false, "M#", getSpeed(runSpeed), "+");
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
  void render(bool doCleanAll) {

    Serial.print(F("render "));
    Serial.print(menu);
    Serial.print(F(" "));
    Serial.println(subMenu);
    if (menu == 0) {
      ssh.send(doCleanAll, "N#TFTF+H#Welcome!+M#", user.name, "+");
    } else if (menu == 1) {
      if (subMenu == 1) {
        ssh.send(doCleanAll, "H#Select Workout!+N#TTTT+S#Start Last Selected:+s#", wh.getNameById(user.lastSelection), "+");
      } else if (subMenu == 2) {
        ssh.send(doCleanAll, "H#Select Workout!+N#TTTF+S#Other Workouts+s#+");
      } else if (subMenu == 3) {
        ssh.send(doCleanAll, "H#Select Workout!+N#TTTF+S#User Settings+s#+");
      }
    } else if (menu == 3) {
      ssh.send(doCleanAll, "H#Last Workout Details:+N#FTFF+S#", wh.getNameById(user.lastSelection), "+s#", wh.getById(user.lastSelection), "+");
    } else if (menu == 4) {
      ssh.send(doCleanAll, "H#Other workouts:+N#TTTF+S#", wh.getNameById(subMenu), "+s#", wh.getById(subMenu), "+");
    } else if (menu == 5) {
      if (subMenu == 1) {
        ssh.send(doCleanAll, "H#Settings:+N#TTTF+S#Name:+s#", user.name, "+");
      } else if (subMenu == 2) {
        ssh.send(doCleanAll, "H#Settings:+N#TTTF+S#Walk Speed:+s#", getSpeed(user.walkSpeed), "+");
      } else if (subMenu == 20) {
        ssh.send(doCleanAll, "H#Walk Speed:+N#TTTF+M#", getSpeed(user.walkSpeed), "+");
      } else if (subMenu == 3) {
        ssh.send(doCleanAll, "H#Settings:+N#TTTF+S#Run Speed:+s#", getSpeed(user.runSpeed), "+");
      } else if (subMenu == 30) {
        ssh.send(doCleanAll, "H#Run Speed:+N#TTTF+M#", getSpeed(user.runSpeed), "+");
      }
    } else if (menu = 6) {      
      ssh.send(doCleanAll, "M#12:09+");
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
    Serial.print(F("setMenu "));
    Serial.print(newMenu);
    Serial.print(F(" "));
    Serial.println(newSubMenu);
    bool doClear = false;
    if (menu != newMenu) {
      doClear = true;
    }
    menu = newMenu;
    subMenu = newSubMenu;
    inTimer = false;
    timeTick = 0;
    render(doClear);
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
  EEPROMHandler eh;
  WorkoutHandler wh;
  SoftSerialHandler ssh;
  //short workoutTimers[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  short workoutTimers[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
};