#include "Wheel.h"
#include "Pins.h"


Wheel::Wheel() {;} // Constructor

Wheel::~Wheel() {;} // Destructor

void Wheel::setup() {
    Serial.begin(9600);
    pinMode(AIN1, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(PWMA_LEFT, OUTPUT);
    pinMode(STBY_PIN, OUTPUT);
    pinMode(MY_LED, OUTPUT);

    

    stop();
    forward(255);
    
    
}

void Wheel::loop() {
    Serial.println(encoder_count_left_a);
    ;
}


void Wheel::stop() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(STBY_PIN, HIGH);
  analogWrite(PWMA_LEFT, 0);
}

void Wheel::forward(unsigned char speed) {
  digitalWrite(AIN1, 0);
  digitalWrite(BIN1, 0);
  analogWrite(PWMA_LEFT, speed);
}

void Wheel::encoderCountLeftA() {
  encoder_count_left_a++;
}