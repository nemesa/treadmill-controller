//I2C pins:
//SCL -> A5
//SDA -> A4

#define jX A0
#define jY A1
#define jSW 4
#define ssTxPin 13
#define ssRxPin 12
#define displayReadyPin 11

#include "jojoystick.cpp"
#include "menu.cpp"
#include "relay.h"

JojoystickHandler jh;
MenuHandler mh;
RelayHandler rh(10);

bool inTimer = false;

void setup() {
  pinMode(displayReadyPin, INPUT);

  cli();  //stop interrupts

  TCCR1A = 0;  // set entire TCCR1A register to 0
  TCCR1B = 0;  // same for TCCR1B
  TCNT1 = 0;   //initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;  // = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();  //allow interrupts

  Serial.begin(9600);
  Serial.println(F("Setup"));

  if (digitalRead(displayReadyPin) == 0) {
    while (digitalRead(displayReadyPin) != 1) {
      delay(100);
    }
  }

  rh.setup();
  jh.setup(jX, jY, jSW);
  mh.setup(&rh, ssRxPin, ssTxPin);
}

void loop() {

  jh.loop();
  if (jh.isDownReleased()) {
    mh.down();
  }
  if (jh.isUpReleased()) {
    mh.up();
  }
  if (jh.isLeftReleased()) {
    mh.left();
  }
  if (jh.isRightReleased()) {
    mh.right();
  }
  if (jh.isSWReleased()) {
    mh.select();
  }

  if (inTimer) {
    inTimer = false;
    mh.timerTick();
  }

  delay(10);
}


ISR(TIMER1_COMPA_vect) {  //timer1 interrupt 1Hz toggles pin 13 (LED)
                          //generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  inTimer = true;
}
