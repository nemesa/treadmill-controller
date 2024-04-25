#include "Arduino.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



class DisplayHandler {
public:
  void setup() {
    _display = new Adafruit_SSD1306(4); //OLED_RESET=4
    _display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
    // init done
    // Show image buffer on the display hardware.
    // Since the buffer is intialized with an Adafruit splashscreen
    // internally, this will display the splashscreen.
    //display.display();
    //delay(2000);
    // Clear the buffer.
    _display.clearDisplay();

    // draw the first ~12 characters in the font

    _display.setTextSize(2);
    _display.setTextColor(WHITE);
    _display.clearDisplay();
    _display.setCursor(0, 0);
    _display.println("text");
    _display.display();
  }
private:
 Adafruit_SSD1306 _display; 
};

// void testdrawchar(char* value) {
//   display.fillRect(0, 0, 128, 64, BLACK);

//   display.setCursor(0, 0);
//   display.println(value);

//   display.display();
// }