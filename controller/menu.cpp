#include "Arduino.h"
#include "relay.h"
#include "eeprom.h"
#include "workout.cpp"
#include "display.h"

class MenuHandler {
public:

  void setup(EEPROMHandler* eepromHAndler, RelayHandler* relayHandler, DisplayHandler* displayHandler) {
    Serial.println(F("MenuHandler-setup"));
    rh = relayHandler;
    eh = eepromHAndler;
    dh = displayHandler;
    user = eh->getLastSelectedUser();
    pinMap = eh->getControlPinMap();

    wh.setup();
    setUser(user.num);

    setMenu(0, -1, -1);
    //setMenu(3, -1,-1);
  }
  void down() {
    if (menu == 0) {
      readNextUser();
      dh->main(false, user.name);

    } else if (menu == 1) {
      subMenu = next(1, 3, subMenu, true, true);
      setMenu(1, subMenu, 0);
    } else if (menu == 4) {
      subMenu = next(1, 29, subMenu, true, true);
      setMenu(4, subMenu, 0);
    } else if (menu == 5 && subMenu < 10) {
      subMenu = next(1, 5, subMenu, true, true);
      setMenu(5, subMenu, 0);
    } else if (menu == 5 && subMenu == 10) {
      user.name[subMenu2] = (char)next(32, 122, user.name[subMenu2], true, true);
      setMenu(5, subMenu, subMenu2);
    } else if (menu == 5 && subMenu == 20) {
      walkSpeed = next(1, 160, walkSpeed, false, false);
      dh->main(false, getSpeed(walkSpeed));
    } else if (menu == 5 && subMenu == 30) {
      runSpeed = next(1, 160, runSpeed, false, false);
      dh->main(false, getSpeed(runSpeed));
    } else if (menu == 5 && subMenu > 40 && subMenu <= 49) {
      subMenu = next(41, 46, subMenu, true, true);
      setMenu(5, subMenu, 0);
    } else if (menu == 5 && subMenu > 50 && subMenu <= 59) {
      subMenu = next(51, 56, subMenu, true, true);
      setMenu(5, subMenu, 0);
    }
  }
  void up() {
    if (menu == 0) {
      readPrevUser();
      dh->main(false, user.name);
    } else if (menu == 1) {
      subMenu = next(1, 3, subMenu, false, true);
      setMenu(1, subMenu, 0);
    } else if (menu == 4) {
      subMenu = next(1, 29, subMenu, false, true);
      setMenu(4, subMenu, 0);
    } else if (menu == 5 && subMenu < 10) {
      subMenu = next(1, 5, subMenu, false, true);
      setMenu(5, subMenu, 0);
    } else if (menu == 5 && subMenu == 10) {
      user.name[subMenu2] = (char)next(32, 122, user.name[subMenu2], false, true);
      setMenu(5, subMenu, subMenu2);
    } else if (menu == 5 && subMenu == 20) {
      walkSpeed = next(1, 160, walkSpeed, true, false);
      dh->main(false, getSpeed(walkSpeed));
    } else if (menu == 5 && subMenu == 30) {
      runSpeed = next(1, 160, runSpeed, true, false);
      dh->main(false, getSpeed(runSpeed));
    } else if (menu == 5 && subMenu > 40 && subMenu <= 49) {
      subMenu = next(41, 46, subMenu, false, true);
      setMenu(5, subMenu, 0);
    } else if (menu == 5 && subMenu > 50 && subMenu <= 59) {
      subMenu = next(51, 56, subMenu, false, true);
      setMenu(5, subMenu, 0);
    }
  }
  void left() {
    if (menu == 1) {
      setMenu(0, -1, 0);
    } else if (menu == 3) {
      setMenu(1, 1, 0);
    } else if (menu == 4) {
      setMenu(1, 2, 0);
    } else if (menu == 5) {
      if (subMenu == 10) {
        if (subMenu2 == 0) {
          user = eh->getLastSelectedUser();
          setMenu(5, 1, 0);
        } else {
          subMenu2 = next(0, 6, subMenu2, false, true);
          setMenu(5, subMenu, subMenu2);
        }
      } else if (subMenu == 20) {
        setMenu(5, 2, 0);
      } else if (subMenu == 30) {
        setMenu(5, 3, 0);
      } else if (subMenu > 40 && subMenu <= 49) {
        setMenu(5, 4, 0);
      } else if (subMenu > 50 && subMenu <= 59) {
        if (subMenu2 == 1) {
          setMenu(5, 5, 0);
        } else {
          subMenu2 = next(1, 6, subMenu2, false, true);
          setMenu(5, subMenu, subMenu2);
        }
      } else {
        setMenu(1, 3, 0);
      }
    } else if (menu == 6 && (subMenu == 3 || subMenu == 1)) {
      setMenu(1, 1, 0);
    }
  }
  void right() {
    if (menu == 1) {
      setMenu(3, -1, 0);
    } else if (menu == 5 && subMenu == 10) {
      subMenu2 = next(0, 6, subMenu2, true, true);
      setMenu(5, subMenu, subMenu2);
    } else if (menu == 5 && subMenu > 50 && subMenu <= 59) {
      subMenu2 = next(1, 6, subMenu2, true, true);
      setMenu(5, subMenu, subMenu2);
    }
  }
  void select() {
    if (menu == 0) {
      eh->setLastUser(user.num);
      setMenu(1, 1, 0);
    } else if (menu == 1 && subMenu == 1) {
      setMenu(6, 1, 0);
    } else if (menu == 1 && subMenu == 2) {
      setMenu(4, user.lastSelection, 0);
    } else if (menu == 1 && subMenu == 3) {
      setMenu(5, 1, 0);
    } else if (menu == 3) {
      setMenu(6, 1, 0);
    } else if (menu == 4) {
      user.lastSelection = subMenu;
      eh->writeUserData(user);
      setMenu(6, 1, 0);
    } else if (menu == 5) {
      if (subMenu == 1) {
        setMenu(5, 10, 0);
      } else if (subMenu == 2) {
        setMenu(5, 20, 0);
      } else if (subMenu == 3) {
        setMenu(5, 30, 0);
      } else if (subMenu == 4) {
        setMenu(5, 41, 0);
      } else if (subMenu == 5) {
        setMenu(5, 51, 0);
      } else if (subMenu == 20) {
        user.walkSpeed = walkSpeed;
        eh->writeUserData(user);
        setMenu(5, 2, 0);
      } else if (subMenu == 30) {
        user.runSpeed = runSpeed;
        eh->writeUserData(user);
        setMenu(5, 3, 0);
      } else if (subMenu == 10) {
        eh->writeUserData(user);
        setMenu(5, 1, 0);
      } else if (subMenu > 40 && subMenu <= 49) {
        uint8_t pinNo = subMenu - 40;
        rh->pinTest(&pinMap, pinNo);
      } else if (subMenu == 51) {
        pinMap.startStop = subMenu2;
        eh->writeControlPinMap(pinMap);
      } else if (subMenu == 52) {
        pinMap.speedInc = subMenu2;
        eh->writeControlPinMap(pinMap);
      } else if (subMenu == 53) {
        pinMap.speedDec = subMenu2;
        eh->writeControlPinMap(pinMap);
      } else if (subMenu == 54) {
        pinMap.speed30 = subMenu2;
        eh->writeControlPinMap(pinMap);
      } else if (subMenu == 55) {
        pinMap.speed60 = subMenu2;
        eh->writeControlPinMap(pinMap);
      } else if (subMenu == 56) {
        pinMap.speed100 = subMenu2;
        eh->writeControlPinMap(pinMap);
      }
    } else if (menu == 6 && subMenu == 1) {
      setMenu(6, 2, 0);
    } else if (menu == 6 && subMenu == 2) {
      setMenu(6, 3, 0);
    } else if (menu == 6 && subMenu == 3) {
      setMenu(6, 2, 0);
    } else if (menu == 6 && subMenu == 4) {
      setMenu(1, 1, 0);
    }
  }
  void timerTick() {
    if (menu == 6 && subMenu == 2) {
      if (!inTimer) {
        Serial.print(F("timeTick-"));
        Serial.print(timeTick);
        Serial.print(F(" - hWS: "));
        Serial.println(hasWorkoutStarted ? F("T") : F("F"));
        inTimer = true;


        if (hasWorkoutStarted) {

          char* timeToShow = "X: 00:00";
          getTime(timeToShow, workoutSection, timeTick);
          dh->main(false, timeToShow);

          short currentTarget = workoutTimers[workoutSection];
          if (isRunningInSection(workoutSection)) {
            currentTarget = currentTarget * -1;
          }
          short timeLeft = currentTarget - timeTick;

          Serial.print(F("timeLeft-"));
          Serial.println(timeLeft);
          if (timeLeft <= 0) {
            timeTick = -1;
            workoutSection++;
            dh->header(false, getWorkoutHeader(workoutSection));
            if (workoutTimers[workoutSection] == 0) {
              setMenu(6, 4, 0);
            } else {
              if (isRunningInSection(workoutSection)) {
                rh->toSpeed(&pinMap, user.runSpeed);
              } else {
                rh->toSpeed(&pinMap, user.walkSpeed);
              }
            }
          }

          timeTick++;
        } else {
          if (startTimeTick < 6) {
            char num[2] = { 0, 0 };
            short t = 5 - startTimeTick;
            num[0] = (char)(48 + t);
            Serial.println(num[0]);

            if (startTimeTick == 4) {
              if (isRunningInSection(workoutSection)) {
                rh->toSpeed(&pinMap, user.runSpeed);
              } else {
                rh->toSpeed(&pinMap, user.walkSpeed);
              }
            }

            if (startTimeTick == 5) {
              char* timeToShowAtStart = "Y: 00:00";
              getTime(timeToShowAtStart, workoutSection, timeTick);
              dh->headerWithMain(false, getWorkoutHeader(workoutSection), timeToShowAtStart);
              hasWorkoutStarted = true;
            } else {
              dh->main(false, num);
            }
          }
          startTimeTick++;
        }

        inTimer = false;
      }
    }
  }

private:
  uint8_t menu = -1;
  uint8_t subMenu = -1;
  uint8_t subMenu2 = -1;
  uint8_t walkSpeed = -1;
  uint8_t runSpeed = -1;
  bool inTimer = false;
  int timeTick = 0;
  bool hasWorkoutStarted = false;
  short startTimeTick = 0;
  short workoutSection = 0;
  void render(bool doCleanAll) {

    Serial.print(F("render "));
    Serial.print(menu);
    Serial.print(F(" "));
    Serial.print(subMenu);
    Serial.print(F(" "));
    Serial.println(subMenu2);
    if (menu == 0) {
      dh->headerNavigationWithMain(doCleanAll, "Welcome!", true, false, true, false, user.name);
    } else if (menu == 1) {
      if (subMenu == 1) {
        dh->headerNavigationSmallLines(doCleanAll, "Select Workout!", true, true, true, true, "Start Last Selected:", wh.getNameById(user.lastSelection));
      } else if (subMenu == 2) {
        dh->headerNavigationSmallLines(doCleanAll, "Select Workout!", true, true, true, false, "Other Workouts", "");
      } else if (subMenu == 3) {
        dh->headerNavigationSmallLines(doCleanAll, "Select Workout!", true, true, true, false, "User Settings", "");
      }
    } else if (menu == 3) {
      dh->headerNavigationSmallLines(doCleanAll, "Last Workout Details:", false, true, false, false, wh.getNameById(user.lastSelection), wh.getById(user.lastSelection));

    } else if (menu == 4) {
      dh->headerNavigationSmallLines(doCleanAll, "Other workouts:", true, true, true, false, wh.getNameById(subMenu), wh.getById(subMenu));
    } else if (menu == 5) {
      if (subMenu == 1) {
        dh->headerNavigationSmallLines(doCleanAll, "Settings:", true, true, true, true, "Name", user.name);
      } else if (subMenu == 10) {
        char* indicator = "^^^^^^^";
        for (int i = 0; i <= 6; i++) {
          indicator[i] = subMenu2 != i ? (char)32 : (char)94;  // SPACE OR ^
        }

        dh->headerNavigationSmallLines(doCleanAll, "Name:", true, true, true, false, user.name, indicator);
      } else if (subMenu == 2) {
        dh->headerNavigationSmallLines(doCleanAll, "Settings:", true, true, true, false, "Walk Speed:", getSpeed(user.walkSpeed));
      } else if (subMenu == 20) {
        dh->headerNavigationWithMain(doCleanAll, "Walk Speed:", true, true, true, false, getSpeed(user.walkSpeed));
      } else if (subMenu == 3) {
        dh->headerNavigationSmallLines(doCleanAll, "Settings:", true, true, true, false, "Run Speed:", getSpeed(user.runSpeed));
      } else if (subMenu == 30) {
        dh->headerNavigationWithMain(doCleanAll, "Run Speed:", true, true, true, false, getSpeed(user.runSpeed));
      } else if (subMenu == 4) {
        dh->headerNavigationSmallLines(doCleanAll, "Settings:", true, true, true, false, "Control pin test", "");
      } else if (subMenu > 40 && subMenu <= 46) {
        uint8_t pinNo = subMenu - 40;
        char* pinNoStr = "  Pin:0";
        pinNoStr[6] = (char)(48 + pinNo);
        dh->headerNavigationWithMain(doCleanAll, "Control pin test:", true, true, true, false, pinNoStr);
      } else if (subMenu == 5) {
        dh->headerNavigationSmallLines(doCleanAll, "Settings:", true, true, true, false, "Control pin setup", "");
      } else if (subMenu == 51) {
        if (subMenu2 == 0) {
          subMenu2 = pinMap.startStop;
        }
        char* pinNoStr = "  Pin:0";
        pinNoStr[6] = (char)(48 + subMenu2);
        dh->headerNavigationSmallLines(doCleanAll, "Control pin setup:", true, true, true, true, "Start/Stop", pinNoStr);
      } else if (subMenu == 52) {
        if (subMenu2 == 0) {
          subMenu2 = pinMap.speedInc;
        }
        char* pinNoStr = "  Pin:0";
        pinNoStr[6] = (char)(48 + subMenu2);
        dh->headerNavigationSmallLines(doCleanAll, "Control pin setup:", true, true, true, true, "Speed inc. 0.1", pinNoStr);
      } else if (subMenu == 53) {
        if (subMenu2 == 0) {
          subMenu2 = pinMap.speedDec;
        }
        char* pinNoStr = "  Pin:0";
        pinNoStr[6] = (char)(48 + subMenu2);
        dh->headerNavigationSmallLines(doCleanAll, "Control pin setup:", true, true, true, true, "Speed dec. 0.1", pinNoStr);
      } else if (subMenu == 54) {
        if (subMenu2 == 0) {
          subMenu2 = pinMap.speed30;
        }
        char* pinNoStr = "  Pin:0";
        pinNoStr[6] = (char)(48 + subMenu2);
        dh->headerNavigationSmallLines(doCleanAll, "Control pin setup:", true, true, true, true, "Speed to 3.0", pinNoStr);
      } else if (subMenu == 55) {
        if (subMenu2 == 0) {
          subMenu2 = pinMap.speed60;
        }
        char* pinNoStr = "  Pin:0";
        pinNoStr[6] = (char)(48 + subMenu2);
        dh->headerNavigationSmallLines(doCleanAll, "Control pin setup:", true, true, true, true, "Speed to 6.0", pinNoStr);
      } else if (subMenu == 56) {
        if (subMenu2 == 0) {
          subMenu2 = pinMap.speed100;
        }
        char* pinNoStr = "  Pin:0";
        pinNoStr[6] = (char)(48 + subMenu2);
        dh->headerNavigationSmallLines(doCleanAll, "Control pin setup:", true, true, true, true, "Speed to 10.0", pinNoStr);
      }
    } else if (menu = 6) {
      if (subMenu == 1) {
        hasWorkoutStarted = false;
        timeTick = 0;
        workoutSection = 0;
        dh->headerNavigationWithMain(false, wh.getNameById(user.lastSelection), false, true, false, false, "START");
        for (uint8_t i = 0; i < 20; i++) {
          workoutTimers[i] = 0;
        }

        wh.getTimersById(workoutTimers, user.lastSelection);
        for (uint8_t i = 0; i < 20; i++) {
          Serial.print(workoutTimers[i]);
          Serial.print(F(", "));
        }
        Serial.println(F(""));
      }
      if (subMenu == 2) {
        hasWorkoutStarted = false;
        startTimeTick = 0;
        dh->header(true, "starting...");
        rh->start(&pinMap);
      }
      if (subMenu == 3) {
        hasWorkoutStarted = false;
        startTimeTick = 0;
        rh->stop(&pinMap);
        dh->headerNavigationWithMain(doCleanAll, "Paused", false, true, false, false, "START");
      }
      if (subMenu == 4) {
        hasWorkoutStarted = false;
        startTimeTick = 0;
        dh->headerWithMain(false, "Finished!", "EXIT");
        rh->stop(&pinMap);
      }
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
  void setMenu(short newMenu, short newSubMenu, short newSubMenu2) {
    Serial.print(F("setMenu "));
    Serial.print(newMenu);
    Serial.print(F(" "));
    Serial.print(newSubMenu);
    Serial.print(F(" "));
    Serial.println(newSubMenu2);
    bool doClear = false;
    if (menu != newMenu) {
      doClear = true;
    }
    menu = newMenu;
    subMenu = newSubMenu;
    subMenu2 = newSubMenu2;
    inTimer = false;
    render(doClear);
  };
  char* getSpeed(uint8_t speed) {
    Serial.print(F("getSpeed "));
    Serial.println(speed);

    char* result = "00.0";
    if (speed < 100) {
      result[0] = (char)32;  //SPACE
    }
    if (speed < 10) {
      result[1] = (char)48;  //0
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
  void getTime(char* result, short workoutSection, short ticks) {
    short currentTarget = workoutTimers[workoutSection];
    /*Serial.print(F("getTime ws:"));
    Serial.print(workoutSection);
    Serial.print(F(" target: "));
    Serial.print(currentTarget);
    Serial.print(F(" tick: "));
    Serial.println(ticks);*/

    if (currentTarget == 0) {
      result[0] = (char)32;  //SPACE
      result[1] = (char)32;  //SPACE
      result[2] = (char)69;  //E
      result[3] = (char)78;  //N
      result[4] = (char)68;  //D
      result[5] = (char)32;  //SPACE
      result[6] = (char)32;  //SPACE
      result[7] = (char)32;  //SPACE
    } else {

      result[0] = (char)88;  //X
      result[1] = (char)58;  //:
      result[2] = (char)32;  //SPACE
      result[3] = (char)48;  //0
      result[4] = (char)48;  //0
      result[5] = (char)58;  //:
      result[6] = (char)48;  //0
      result[7] = (char)48;  //0

      bool isRunning = isRunningInSection(workoutSection);
      if (isRunning) {
        result[0] = (char)82;  //R
        currentTarget = currentTarget * -1;
      } else {
        result[0] = (char)87;  //W
      }

      short timeLeft = currentTarget - ticks;

      if (timeLeft > 60) {
        short mins = timeLeft / 60;
        short sec = timeLeft % 60;

        if (mins > 9) {
          result[3] = (char)(48 + mins / 10);
          result[4] = (char)(48 + mins % 10);
        } else {
          result[3] = (char)48;
          result[4] = (char)(48 + mins);
        }

        if (sec > 9) {
          result[6] = (char)(48 + sec / 10);
          result[7] = (char)(48 + sec % 10);
        } else {
          result[6] = (char)48;
          result[7] = (char)(48 + sec);
        }

      } else if (timeLeft == 60) {
        result[3] = (char)48;  //0
        result[4] = (char)49;  //1
        result[6] = (char)48;  //0
        result[7] = (char)48;  //0

      } else {
        result[4] = (char)48;  //0
        if (timeLeft > 9) {
          result[6] = (char)(48 + timeLeft / 10);
          result[7] = (char)(48 + timeLeft % 10);
        } else {
          result[6] = (char)48;
          result[7] = (char)(48 + timeLeft);
        }
      }
    }
    // char(*p)[9];
    // p = &result;
    // return p;
    return result;
  }
  char* getWorkoutHeader(short workoutSection) {
    char* result = "X: 00:00 -> X: 00:00";
    char* current = "X: 00:00";
    getTime(current, workoutSection, 0);
    for (int i = 0; i < 8; i++) {
      result[i] = current[i];
    }
    char* next = "X: 00:00";
    getTime(next, workoutSection + 1, 0);
    for (int j = 0; j < 8; j++) {
      result[(12 + j)] = next[j];
    }
    return result;
  }
  bool isRunningInSection(short workoutSection) {
    short currentTarget = workoutTimers[workoutSection];
    if (currentTarget > 0) {
      return false;
    }
    return true;
  }
  void setUser(uint8_t num) {
    user = eh->readUser(num);
    walkSpeed = user.walkSpeed;
    runSpeed = user.runSpeed;
  }
  uint8_t next(uint8_t min, uint8_t max, uint8_t current, bool isUp, bool allowOverFlow) {
    if (isUp) {
      current++;
      if (current > max) {
        if (allowOverFlow) {
          current = min;
        } else {
          current = max;
        }
      }
    } else {
      current--;
      if (current < min) {
        if (allowOverFlow) {
          current = max;
        } else {
          current = min;
        }
      }
    }
    return current;
  }
  UserDataStruct user;
  ControlPinMapStruct pinMap;
  EEPROMHandler* eh;
  WorkoutHandler wh;
  DisplayHandler* dh;
  RelayHandler* rh;
  short workoutTimers[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
};