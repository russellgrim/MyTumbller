#include "Controller.h" 
#include "Wheel.h"
#include "Led.h"

#include "Pins.h"
#include "PinChangeInt.h"



// instantiation
Wheel left_wheel;
Led led_1;

int incomingByte = 0;
String command;


void setup() {
  // left_wheel.setup();
  led_1.setup();
  
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_A_PIN), encoderCountLeftA, CHANGE);
}

// the loop function runs over and over again forever
void loop() {
  // left_wheel.loop();
  led_1.loop();
  read_serial();
}

void encoderCountLeftA() {
  left_wheel.encoderCountLeftA();
}

void read_serial() {
  // send data only when you receive data:
  if ( Serial.available() ) {
    // read the incoming byte:
    char c = Serial.read();

    if (c == '\n') { // if end of command
      parse_command(command);
      command = ""; //empty command
    } else {
      command += c; // append char to command
    }
  }
}

void parse_command(String com){
  if (com.equalsIgnoreCase("led start blinking") ){
    led_1.start_blinking();
  } else if (com.equalsIgnoreCase("led stop blinking") ){
    led_1.stop_blinking();
  }
}
