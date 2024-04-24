#include <ezButton.h>
#define jX  A0
#define jY  A1
#define sw  10

ezButton button(sw);
  
void setup() {
 Serial.begin(115200);
  Serial.println("Setup"); 
  pinMode(jX,INPUT);
  pinMode(jY,INPUT);
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
}
int x = 0;
int y = 0;
int bValue = 0;

void loop() {
  button.loop(); // MUST call the loop() function first
  // put your main code here, to run repeatedly:
  x = analogRead(jX);
  y = analogRead(jY);
  int buttonState = digitalRead(sw);
  // Read the button value
  bValue = button.getState();

  if (button.isPressed()) {
    Serial.println("The button is pressed");
    // TODO do something here
  }

  if (button.isReleased()) {
    Serial.println("The button is released");
    // TODO do something here
  }

  if(x<300){
  Serial.println("Left");
  }

  if(x>600){
  Serial.println("Right");
  }
  

  if(y<300){
  Serial.println("Up");
  }

  if(y>600){
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

