#include "Pir.h"
#include <Arduino.h>

#define PIR_CALIBRATE_TIME 10000


Pir::Pir(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
}

void Pir::detectPresence() {
    detected = digitalRead(pin) == HIGH;
}

bool Pir::isDetected() {
    return detected;
}

void Pir::calibrate() {
    delay(10000);
}
