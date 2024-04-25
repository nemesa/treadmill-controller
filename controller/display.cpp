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
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
    // init done
    // Show image buffer on the display hardware.
    // Since the buffer is intialized with an Adafruit splashscreen
    // internally, this will display the splashscreen.
    //display.display();
    //delay(2000);
    // Clear the buffer.
    display.clearDisplay();

    // draw the first ~12 characters in the font

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("text");
    display.display();
  }
  void cleanAll() {
    display.fillRect(0, 0, 128, 64, BLACK);
    display.display();
  }
  void debug(char* text) {
    display.setTextSize(1);
    display.fillRect(0, 0, 128, 8, BLACK);
    display.setCursor(0, 0);
    display.println(text);
    display.display();
  }
  void header(char* text) {
    display.setTextSize(1);
    display.fillRect(0, 0, 128, 8, BLACK);
    display.setCursor(0, 0);
    display.println(text);
    display.drawFastHLine(0, 9, 128, WHITE);
    display.display();
  }
  void main(char* text) {
    display.setTextSize(2);
    display.fillRect(0, 10, 128, 16, BLACK);
    display.setCursor(0, 10);
    display.println(text);
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