#include "Arduino.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



class DisplayHandler {
public:
  void setup() {
    Serial.println("DisplayHandler-setup");
    display = new Adafruit_SSD1306(4);          //OLED_RESET=4
    delay(50);
    //Serial.println("display.begin");
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
    delay(50);
    //Serial.println("display.clearDisplay");
    display.clearDisplay();

    // draw the first ~12 characters in the font

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("STARTING...");
    display.display();
  }
  void cleanAll() {
    display.fillRect(0, 0, 127, 31, BLACK);
    display.display();
  }
  void debug(char* text) {
    display.setTextSize(1);
    display.fillRect(0, 0, 127, 8, BLACK);
    display.setCursor(0, 0);
    display.println(text);
    display.display();
  }
  void header(char* text) {
    display.setTextSize(1);
    display.fillRect(0, 0, 127, 8, BLACK);
    display.setCursor(0, 0);
    display.println(text);
    display.drawFastHLine(0, 9, 127, WHITE);
    display.display();
  }
  void main(char* text) {
    display.setTextSize(2);
    display.fillRect(7, 14, 115, 14, BLACK);
    display.setCursor(7, 14);
    display.println(text);
    display.display();
  }
  void mainSmallLine1(char* text) {
    display.setTextSize(1);
    display.fillRect(7, 14, 115, 8, BLACK);
    display.setCursor(7, 14);
    display.println(text);
    display.display();
  }
  void mainSmallLine2(char* text) {
    display.setTextSize(1);
    display.fillRect(7, 22, 115, 8, BLACK);
    display.setCursor(7, 22);
    display.println(text);
    display.display();
  }
  void mainSmallLine2Str(String text) {
    display.setTextSize(1);
    display.fillRect(7, 22, 115, 8, BLACK);
    display.setCursor(7, 22);
    display.println(text);
    display.display();
  }
  void navigationOptions(bool hasUp, bool hasLeft, bool hasDown, bool hasRight) {

    if (hasUp) {
      display.drawTriangle(64, 10, 62, 12, 66, 12, WHITE);
    } else {
      display.drawTriangle(64, 10, 62, 12, 66, 12, BLACK);
    }

    if (hasDown) {
      display.drawTriangle(64, 31, 62, 29, 66, 29, WHITE);
    } else {
      display.drawTriangle(64, 31, 62, 29, 66, 29, BLACK);
    }

    if (hasLeft) {
      display.drawTriangle(0, 20, 2, 18, 2, 22, WHITE);
    } else {
      display.drawTriangle(0, 20, 2, 18, 2, 22, BLACK);
    }

    if (hasRight) {
      display.drawTriangle(127, 20, 125, 18, 125, 22, WHITE);
    } else {
      display.drawTriangle(127, 20, 125, 18, 125, 22, BLACK);
    }

    display.display();
  }
private:
  Adafruit_SSD1306 display;
};

// void testdrawchar(char* value) {
//   display.fillRect(0, 0, 128, 64, BLACK);

//   display.setCursor(0, 0);
//   display.println(value);

//   display.display();
// }