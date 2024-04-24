//I2C pins:
//SCL -> A5
//SDA -> A4

#include <ezButton.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define jX A0
#define jY A1
#define sw 10

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define SSD1306_LCDHEIGHT 64
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

ezButton button(sw);

void setup() {
  Serial.begin(115200);
  Serial.println("Setup");
  pinMode(jX, INPUT);
  pinMode(jY, INPUT);
  button.setDebounceTime(50);  // set debounce time to 50 milliseconds

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
  display.println("");
  display.display();
}
int x = 0;
int y = 0;
int bValue = 0;

void loop() {
  button.loop();  // MUST call the loop() function first
  // put your main code here, to run repeatedly:
  x = analogRead(jX);
  y = analogRead(jY);
  int buttonState = digitalRead(sw);
  // Read the button value
  bValue = button.getState();

  if (button.isPressed()) {
    testdrawchar("BUTn DOWN");
    Serial.println("The button is pressed");
    // TODO do something here
  }

  if (button.isReleased()) {
    //display.fillRect(0, 0, 128, 64, BLACK);
  display.clearDisplay();
    display.display();

    Serial.println("The button is released");
    // TODO do something here
  }

  if (x < 300) {
    testdrawchar("LEFT");
    Serial.println("Left");
  }

  if (x > 600) {
    testdrawchar("RIGHT");
    Serial.println("Right");
  }


  if (y < 300) {
    testdrawchar("UP");
    Serial.println("Up");
  }

  if (y > 600) {
    testdrawchar("DOWN");
    Serial.println("Down");
  }

  //Serial.print("x: ");
  //Serial.print(x);
  //Serial.print(" y: ");
  //Serial.print(y);
  //Serial.print(" sw: ");
  //Serial.println(bValue);
  delay(10);
}

void testdrawchar(char* value) {
  display.fillRect(0, 0, 128, 64, BLACK);

  display.setCursor(0, 0);
  display.println(value);

  display.display();
}
