#include "LightSensorImpl.h"
#include <Arduino.h>


LightSensorImpl::LightSensorImpl(int pin) {
  this->pin = pin;
}

double LightSensorImpl::getLightLevel() {
    int value = analogRead(pin);
    double valueInVolt = ((float) value) * 5/1024;
    return  valueInVolt/5.0;
}
