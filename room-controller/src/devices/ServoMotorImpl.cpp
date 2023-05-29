#include "ServoMotorImpl.h"
#include "Arduino.h"


ServoMotorImpl::ServoMotorImpl(int pin){
  this->pin = pin;  
} 

void ServoMotorImpl::on(){
  motor.attach(pin);    
}

void ServoMotorImpl::setPosition(int angle){
  if (angle > 180) {
    angle = 180;
  } else if (angle < 0) {
    angle = 0;
  }
  float coeff = ((float)(MAX_PULSE_WIDTH - MIN_PULSE_WIDTH))/180.0;
  motor.write(MIN_PULSE_WIDTH + angle * coeff);
}

void ServoMotorImpl::off(){
  motor.detach();    
}
