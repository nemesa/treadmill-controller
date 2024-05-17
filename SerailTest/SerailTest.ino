#include <SoftwareSerial.h>

SoftwareSerial sserial(10, 11); // receive pin=10, transmit pin=11

void setup() {
  Serial.begin(9600);
  sserial.begin(9600); // start serial connection
  // put your setup code here, to run once:

}


void loop() {

  sserial.write("&H_12345|abcdefgh|123456789|abcdfghi$"); 
  //sserial.write("&111$"); 

  delay(5000); // delay required to avoid flooding the other Arduino ("DoS attack")
}
