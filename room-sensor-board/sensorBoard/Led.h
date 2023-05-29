#ifndef __LED__
#define __LED__

#include "Light.h"


/**
 * Class representing a simple led.
*/
class Led : public Light {
private:
    int pin;
    bool ledOn;

public:
    /**
     * Create a new led with given pin.
     * @param pin the pin number of the led.
    */
    Led(int pin);

    /**
     * Switch on the led.
    */
    void switchOn();

    /**
     * Switch off the led.
    */
    void switchOff();
    
    /**
     * Return if the led is on or off.
     * @return true if the led is on otherwise false.
    */
    bool isOn();
};

#endif
