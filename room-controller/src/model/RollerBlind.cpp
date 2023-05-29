#include "RollerBlind.h"
#include "devices/ServoMotorImpl.h"
#include "config.h"


RollerBlind::RollerBlind(int servoPin) {
    this->motor = new ServoMotorImpl(servoPin);
    this->openPercentage = 0;
}

void RollerBlind::on() {
    this->motor->on();
}

void RollerBlind::off() {
    this->motor->off();
}

void RollerBlind::fullRoll() {
    if (openPercentage != MAX_OPEN_PERCENTAGE) {
        // map value and get angle
        int angle = map(MAX_OPEN_PERCENTAGE, MIN_OPEN_PERCENTAGE, MAX_OPEN_PERCENTAGE, 180, 0);
        this->motor->setPosition(angle);
        this->openPercentage = MAX_OPEN_PERCENTAGE;
    }
}

void RollerBlind::fullUnroll() {
    if (openPercentage != MIN_OPEN_PERCENTAGE) {
        // map value and get angle
        int angle = map(MIN_OPEN_PERCENTAGE, MIN_OPEN_PERCENTAGE, MAX_OPEN_PERCENTAGE, 180, 0);
        this->motor->setPosition(angle);
        this->openPercentage = MIN_OPEN_PERCENTAGE;
    }
}

void RollerBlind::roll(int value) {
    // the value is open %
    //  100% open --> 0°
    //  0% open --> 180°

    // check if value is in range 0..100
    if (value < 0) {
        value = 0;
    } else if (value > 100) {
        value = 100;
    }

    // check if value is different from openPercentage
    if (openPercentage != value) {
        // map value and get angle
        int angle = map(value, 0, 100, 180, 0);
        this->motor->setPosition(angle);
        this->openPercentage = value;
    }
}

int RollerBlind::getOpenPercentage() {
    return this->openPercentage;
}
