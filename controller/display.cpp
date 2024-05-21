#include "display.h"

DisplayHandler::DisplayHandler() {
}

void DisplayHandler::setup() {
  Serial.println(F("DisplayHandler-setup"));
  display = new Adafruit_SSD1306(4);  //OLED_RESET=4
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
void DisplayHandler::cleanAll() {
  Serial.println(F("DisplayHandler-cleanAll"));
  display.fillRect(0, 0, 127, 31, BLACK);
  display.display();
}
void DisplayHandler::header(bool doClean, char* text) {
  if (doClean) {
    display.fillRect(0, 0, 127, 31, BLACK);
  }
  display.setTextSize(1);
  display.fillRect(0, 0, 127, 8, BLACK);
  display.setCursor(0, 0);
  display.println(text);
  display.drawFastHLine(0, 9, 127, WHITE);
  display.display();
}
void DisplayHandler::main(bool doClean, char* text) {
  if (doClean) {
    display.fillRect(0, 0, 127, 31, BLACK);
  }
  display.setTextSize(2);
  display.fillRect(7, 14, 117, 15, BLACK);
  display.setCursor(7, 14);
  display.println(text);
  display.display();
}
void DisplayHandler::mainSmallLine1(char* text) {
  display.setTextSize(1);
  display.fillRect(7, 14, 117, 8, BLACK);
  display.setCursor(7, 14);
  display.println(text);
  display.display();
}
void DisplayHandler::mainSmallLine2(char* text) {
  display.setTextSize(1);
  display.fillRect(7, 22, 117, 7, BLACK);
  display.setCursor(7, 22);
  display.println(text);
  display.display();
}
void DisplayHandler::navigationOptions(bool hasUp, bool hasLeft, bool hasDown, bool hasRight) {

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


void DisplayHandler::headerWithMain(bool doClean, char* headerMessage, char* mainMessage) {
  if (doClean) {
    display.fillRect(0, 0, 127, 31, BLACK);
  }

  display.setTextSize(1);
  display.fillRect(0, 0, 127, 8, BLACK);
  display.setCursor(0, 0);
  display.println(headerMessage);
  display.drawFastHLine(0, 9, 127, WHITE);

  display.setTextSize(2);
  display.fillRect(7, 14, 117, 15, BLACK);
  display.setCursor(7, 14);
  display.println(mainMessage);
  display.display();
};

void DisplayHandler::headerNavigationWithMain(bool doClean, char* headerMessage, bool hasNavUp, bool hasNavLeft, bool hasNavDown, bool hasNavRight, char* mainMessage) {
  if (doClean) {
    display.fillRect(0, 0, 127, 31, BLACK);
  }

  display.setTextSize(1);
  display.fillRect(0, 0, 127, 8, BLACK);
  display.setCursor(0, 0);
  display.println(headerMessage);
  display.drawFastHLine(0, 9, 127, WHITE);

  display.setTextSize(2);
  display.fillRect(7, 14, 117, 15, BLACK);
  display.setCursor(7, 14);
  display.println(mainMessage);
  display.display();

  navigationOptions(hasNavUp, hasNavLeft, hasNavDown, hasNavRight);
};
void DisplayHandler::headerNavigationSmallLines(bool doClean, char* headerMessage, bool hasNavUp, bool hasNavLeft, bool hasNavDown, bool hasNavRight, char* sl1, char* sl2) {
  if (doClean) {
    display.fillRect(0, 0, 127, 31, BLACK);
  }

  display.setTextSize(1);
  display.fillRect(0, 0, 127, 8, BLACK);
  display.setCursor(0, 0);
  display.println(headerMessage);
  display.drawFastHLine(0, 9, 127, WHITE);

  display.fillRect(7, 14, 117, 8, BLACK);
  display.setCursor(7, 14);
  display.println(sl1);

  display.fillRect(7, 22, 117, 7, BLACK);
  display.setCursor(7, 22);
  display.println(sl2);

  navigationOptions(hasNavUp, hasNavLeft, hasNavDown, hasNavRight);
};
