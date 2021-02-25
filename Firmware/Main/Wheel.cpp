#include "Wheel.h"
#include "Pins.h"





Wheel::Wheel() {;} // Constructor

Wheel::~Wheel() {;} // Destructor

void Wheel::setup() {
    
    pinMode(AIN1, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(PWMA_LEFT, OUTPUT);
    pinMode(STBY_PIN, OUTPUT);
    pinMode(MY_LED, OUTPUT);

    stop();
    start_time = millis();
    // print_current_time_and_encoder();
}

void Wheel::loop() {
    if (mode  == "PID"){
        _PID_loop();    
    } else if (mode == "Step"){
        ;
    } else if (mode == "None") {
        ;
    } else if (mode == "Position Control"){
        _position_control_pid();
    }else if (mode == "PID Speed control"){
        _speed_control_pid();
    }else if (mode == "PWM step response"){
        _pwm_step_response();
    }
}

void Wheel::_pwm_step_response(){
    if ( millis() - start_time < 15000) {
        if ( _is_sample_time() ) {
            _read_in_sensors();
            print_current_time_and_encoder();
            pwm = 255;
            move(pwm);
        }
    }else {
            stop();
            Serial.println("Done");
            mode = "None";
    }
}

void Wheel::_position_control_pid() {
    if ( millis() - start_time < 15000) {
        if ( _is_sample_time() ) {
            _read_in_sensors();
            _calculate_speed_set_point();
            _calculate_speed_pwm_in();
            print_current_time_and_encoder();
            move(pwm);
        }
    }else {
        stop();
        Serial.println("Done");
        mode = "None";
    }
}

void Wheel::_speed_control_pid() {
    if ( millis() - start_time < 15000) {
        if ( _is_sample_time() ) {
            _read_in_sensors();
            _calculate_speed_pwm_in();
            print_current_time_and_encoder();
            move(pwm);
        }
    }else {
        stop();
        Serial.println("Done");
        mode = "None";
    }
}


void Wheel::_PID_loop (){
    if ( millis() - start_time < 15000) {
        if ( _is_sample_time() ) {
            _read_in_sensors();
            _calculate_speed_set_point();
            _calculate_speed_pwm_in();
            print_current_time_and_encoder();
            move(pwm);
        }
        
    } else {
        stop();
        Serial.println("Done");
        mode = "None";
    }
}

void Wheel::_read_in_sensors(){
    /*!
    read encoders to find position and calculate speed.
    */
    previous_position = current_position; // position from previous sample
    current_position = encoder_count_left_a; 
    speed = (float)( current_position - previous_position ) / (float)sample_period ; //dx/dt
}

void Wheel::print_current_time_and_encoder() {
    Serial.print( millis() - start_time );
    Serial.print(",");
    Serial.print(speed);
    Serial.print(",");
    Serial.print(current_position);
    Serial.print(",");
    Serial.print(target_speed);
    Serial.print(",");
    Serial.print(target_position);
    Serial.print(",");
    Serial.println(pwm);

}

void Wheel::_calculate_speed_set_point(){
    position_error_p = target_position - current_position;
    position_error_i += position_error_p * sample_period;
    target_speed = Kp_position * position_error_p + Ki_position * position_error_i;
    if (target_speed > 0.9) {target_speed = 0.9;}
    if (target_speed < -0.9) {target_speed = -0.9;}

}


void Wheel::_calculate_speed_pwm_in(){
    error_p = target_speed - speed;
    error_i += error_p * sample_period ;
    pwm = Kp * error_p + Ki * error_i;
    if (pwm > 255) {pwm = 255;}
    if (pwm < -255) {pwm = -255;}
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

void Wheel::move (int speed) {
    if (speed >= 0){
        forward(speed);
    }else if (speed < 0 ) {
        carBack(-speed);
    }
}

void Wheel::forward(int speed) {
  digitalWrite(AIN1, 0);
  digitalWrite(BIN1, 0);
  analogWrite(PWMA_LEFT, speed);
}

void Wheel::carBack(int speed)
{
  digitalWrite(AIN1, 1);
  digitalWrite(BIN1, 1);
  analogWrite(PWMA_LEFT, speed);
//   analogWrite(PWMB_RIGHT, speed);
}

void Wheel::encoderCountLeftA() {
  m_direction = digitalRead(BIN1);
  if (!m_direction){
    encoder_count_left_a++;
  }else{
      encoder_count_left_a--;
  }
  
}

void Wheel::encoderCountLeftDecrement() {
  encoder_count_left_a--;
}

void Wheel::set_mode(String modeIn) {
    mode = modeIn;
    start_time = millis(); // restart clock
}