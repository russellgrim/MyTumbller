#include "Wheel.h"
#include "Pins.h"




Wheel::Wheel() {;} // Constructor

Wheel::~Wheel() {;} // Destructor

void Wheel::setup() {
    Serial.begin(115200);
    pinMode(AIN1, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(PWMA_LEFT, OUTPUT);
    pinMode(STBY_PIN, OUTPUT);
    pinMode(MY_LED, OUTPUT);

    stop();
    start_time = millis();
    print_current_time_and_encoder();
}

void Wheel::_calculate_speed(){
    speed = (float)( encoder_count_left_a - previous_position ) / (float)sample_period ; //dx/dt
    previous_position = encoder_count_left_a;
}

void Wheel::print_current_time_and_encoder() {
    Serial.print( millis() - start_time );
    Serial.print(",");
    Serial.println(speed);
}

void Wheel::_calculate_pwm_in(){
    error_p = target_speed - speed;
    error_i += error_p;
    pwm = Kp * error_p + Ki * error_i;
    if (pwm > 255) {pwm = 255;}
}

void Wheel::loop() {
    
    if ( millis() - start_time < 15000) {
        if ( _is_sample_time() ) {
            _calculate_speed();
            _calculate_pwm_in();
            print_current_time_and_encoder();
            forward(pwm);
        }
        
    } else {
        stop();
    }
}

bool Wheel::_is_sample_time(){
    if (millis() - previous_sample_time > sample_period){
        previous_sample_time = millis();
        return true;
    }else {
        return false;
    }
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