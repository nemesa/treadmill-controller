#include "Arduino.h"
#include "relay.h"
#include "eeprom.h"
#include "workout.cpp"
#include "softserial.h"

class MenuHandler {
public:

  void setup(EEPROMHandler* eepromHAndler, RelayHandler* relayHandler, SoftSerialHandler* softSerialHandler, int ssRx, int ssTx) {
    Serial.println(F("MenuHandler-setup"));
    rh = relayHandler;
    eh = eepromHAndler;
    ssh = softSerialHandler;
    user = eh->getLastSelectedUser();

    wh.setup();
    user = eh->getLastSelectedUser();
    setUser(user.num);

    //setMenu(0, -1);
    setMenu(5, 4);
  }
  void down() {
    if (menu == 0) {
      readNextUser();
      ssh->sendMain(false, user.name);

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
      if (subMenu == 6) {
        subMenu = 1;
      }
      setMenu(5, subMenu);
    } else if (menu == 5 && subMenu > 40 && subMenu <= 49) {
      subMenu = subMenu + 1;
      if (subMenu == 47) {
        subMenu = 41;
      }
      setMenu(5, subMenu);
    } else if (menu == 5 && subMenu == 20) {
      walkSpeed = walkSpeed - 1;
      if (walkSpeed == 0) {
        walkSpeed = 1;
      }
      ssh->sendMain(false, getSpeed(walkSpeed));
    } else if (menu == 5 && subMenu == 30) {
      runSpeed = runSpeed - 1;
      if (runSpeed == 0) {
        runSpeed = 1;
      }
      ssh->sendMain(false, getSpeed(runSpeed));
    }
  }
  void up() {
    if (menu == 0) {
      readPrevUser();
      ssh->sendMain(false, user.name);
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
        subMenu = 5;
      }
      setMenu(5, subMenu);
    } else if (menu == 5 && subMenu > 40 && subMenu <= 49) {
      subMenu = subMenu - 1;
      if (subMenu == 40) {
        subMenu = 46;
      }
      setMenu(5, subMenu);
    } else if (menu == 5 && subMenu == 20) {
      walkSpeed = walkSpeed + 1;
      if (walkSpeed == 161) {
        walkSpeed = 160;
      }
      ssh->sendMain(false, getSpeed(walkSpeed));
    } else if (menu == 5 && subMenu == 30) {
      runSpeed = runSpeed + 1;
      if (runSpeed == 161) {
        runSpeed = 160;
      }
      ssh->sendMain(false, getSpeed(runSpeed));
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
    } else if (menu == 6 && (subMenu == 3 || subMenu == 1)) {
      setMenu(1, 1);
    }
  }
  void right() {
    if (menu == 1) {
      setMenu(3, -1);
    }
  }
  void select() {
    if (menu == 0) {
      eh->setLastUser(user.num);
      setMenu(1, 1);
    } else if (menu == 1 && subMenu == 1) {
      setMenu(6, 1);
    } else if (menu == 1 && subMenu == 2) {
      setMenu(4, user.lastSelection);
    } else if (menu == 1 && subMenu == 3) {
      setMenu(5, 1);
    } else if (menu == 3) {
      setMenu(6, 1);
    } else if (menu == 4) {
      user.lastSelection = subMenu;
      eh->writeUserData(user);
      setMenu(6, 1);
    } else if (menu == 5) {
      if (subMenu == 1) {
      } else if (subMenu == 2) {
        setMenu(5, 20);
      } else if (subMenu == 3) {
        setMenu(5, 30);
      } else if (subMenu == 4) {
        setMenu(5, 41);
      } else if (subMenu == 5) {
        setMenu(5, 50);
      } else if (subMenu == 20) {
        user.walkSpeed = walkSpeed;
        eh->writeUserData(user);
        setMenu(5, 2);
      } else if (subMenu == 30) {
        user.runSpeed = runSpeed;
        eh->writeUserData(user);
        setMenu(5, 3);
      } else if (subMenu > 40 && subMenu <= 49) { 
        uint8_t pinNo = subMenu - 40;       
        rh->pinTest(pinNo);
        
      }
    } else if (menu == 6 && subMenu == 1) {
      setMenu(6, 2);
    } else if (menu == 6 && subMenu == 2) {
      setMenu(6, 3);
    } else if (menu == 6 && subMenu == 3) {
      setMenu(6, 2);
    } else if (menu == 6 && subMenu == 4) {
      setMenu(1, 1);
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
          ssh->sendMain(false, timeToShow);

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
            ssh->sendHeader(false, getWorkoutHeader(workoutSection));
            if (workoutTimers[workoutSection] == 0) {
              setMenu(6, 4);
            } else {
              if (isRunningInSection(workoutSection)) {
                rh->toSpeed(user.runSpeed);
              } else {
                rh->toSpeed(user.walkSpeed);
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
                rh->toSpeed(user.runSpeed);
              } else {
                rh->toSpeed(user.walkSpeed);
              }
            }

            if (startTimeTick == 5) {
              char* timeToShowAtStart = "Y: 00:00";
              getTime(timeToShowAtStart, workoutSection, timeTick);
              ssh->sendHeaderWithMain(false, getWorkoutHeader(workoutSection), timeToShowAtStart);
              hasWorkoutStarted = true;
            } else {
              ssh->sendMain(false, num);
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
    Serial.println(subMenu);
    if (menu == 0) {
      ssh->sendHeaderNavigationWithMain(doCleanAll, "Welcome!", "TFTF", user.name);
    } else if (menu == 1) {
      if (subMenu == 1) {
        ssh->sendHeaderNavigationSmallLines(doCleanAll, "Select Workout!", "TTTT", "Start Last Selected:", wh.getNameById(user.lastSelection));
      } else if (subMenu == 2) {
        ssh->sendHeaderNavigationSmallLines(doCleanAll, "Select Workout!", "TTTF", "Other Workouts", "");
      } else if (subMenu == 3) {
        ssh->sendHeaderNavigationSmallLines(doCleanAll, "Select Workout!", "TTTF", "User Settings", "");
      }
    } else if (menu == 3) {
      ssh->sendHeaderNavigationSmallLines(doCleanAll, "Last Workout Details:", "FTFF", wh.getNameById(user.lastSelection), wh.getById(user.lastSelection));

    } else if (menu == 4) {
      ssh->sendHeaderNavigationSmallLines(doCleanAll, "Other workouts:", "TTTF", wh.getNameById(subMenu), wh.getById(subMenu));
    } else if (menu == 5) {
      if (subMenu == 1) {
        ssh->sendHeaderNavigationSmallLines(doCleanAll, "Settings:", "TTTF", "Name", user.name);
      } else if (subMenu == 2) {
        ssh->sendHeaderNavigationSmallLines(doCleanAll, "Settings:", "TTTF", "Walk Speed:", getSpeed(user.walkSpeed));
      } else if (subMenu == 20) {
        ssh->sendHeaderNavigationWithMain(doCleanAll, "Walk Speed:", "TTTF", getSpeed(user.walkSpeed));
      } else if (subMenu == 3) {
        ssh->sendHeaderNavigationSmallLines(doCleanAll, "Settings:", "TTTF", "Run Speed:", getSpeed(user.runSpeed));
      } else if (subMenu == 30) {
        ssh->sendHeaderNavigationWithMain(doCleanAll, "Run Speed:", "TTTF", getSpeed(user.runSpeed));
      } else if (subMenu == 4) {
        ssh->sendHeaderNavigationSmallLines(doCleanAll, "Settings:", "TTTF", "Control pin test", "");
      } else if (subMenu > 40 && subMenu <= 46) {
        uint8_t pinNo = subMenu - 40;
        char* pinNoStr = "  Pin:0";
        pinNoStr[6] = (char)(48 + pinNo);
        ssh->sendHeaderNavigationWithMain(doCleanAll, "Control pin test:", "TTTF", pinNoStr);
      } else if (subMenu == 5) {
        ssh->sendHeaderNavigationSmallLines(doCleanAll, "Settings:", "TTTF", "Control pin setup", "");
      } else if (subMenu == 50) {
        ssh->sendHeaderNavigationWithMain(doCleanAll, "Control pin setup:", "TTTF", "1");
      }
    } else if (menu = 6) {
      if (subMenu == 1) {
        hasWorkoutStarted = false;
        timeTick = 0;
        workoutSection = 0;
        ssh->sendHeaderNavigationWithMain(false, wh.getNameById(user.lastSelection), "FTFF", "START");
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
        ssh->sendHeader(true, "starting...");
        rh->start();
      }
      if (subMenu == 3) {
        hasWorkoutStarted = false;
        startTimeTick = 0;
        rh->stop();
        ssh->sendHeaderNavigationWithMain(doCleanAll, "Paused", "FTFF", "START");
      }
      if (subMenu == 4) {
        hasWorkoutStarted = false;
        startTimeTick = 0;
        ssh->sendHeaderWithMain(false, "Finished!", "EXIT");
        rh->stop();
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
  void setMenu(short newMenu, short newSubMenu) {
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
  UserDataStruct user;
  EEPROMHandler* eh;
  WorkoutHandler wh;
  SoftSerialHandler* ssh;
  RelayHandler* rh;
  short workoutTimers[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
};