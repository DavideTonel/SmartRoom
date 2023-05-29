#include "Led.h"
#include <Arduino.h>


Led::Led(int pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
    this->ledOn = false;
}

void Led::switchOn() {
    if (ledOn != true) {
        digitalWrite(pin, HIGH);
        ledOn = true;
    }
}

void Led::switchOff() {
    if (ledOn != false) {
        digitalWrite(pin, LOW);
        ledOn = false;
    }
}

bool Led::isOn() {
    return ledOn;
}
