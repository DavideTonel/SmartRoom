#ifndef __LIGHTSENSORIMPL__
#define __LIGHTSENSORIMPL__

#include "LightSensor.h"


/**
 * Class representing a simple light sensor.
*/
class LightSensorImpl : public LightSensor {
private:
    int pin;

public:
    /**
     * Create a new light sensor with the given pin.
     * @param pin the given pin.
    */
    LightSensorImpl(int pin);

    /**
     * Get the light level.
     * @return the light level.
    */
    double getLightLevel();
};

#endif
