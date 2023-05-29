#ifndef __ROOMSENSORBOARD__
#define __ROOMSENSORBOARD__

#include "Light.h"
#include "LightSensor.h"
#include "Pir.h"


/**
 * Class representing a sensor-board.
*/
class RoomSensorBoard {
private:
    bool presenceDetected;
    double lightLevel;

    Pir* pir;
    LightSensor* lightSensor;
    Light* light;

public:
    /**
     * Create a new room sensor board with the given pins.
     * @param pirPin the pin of the pir.
     * @param lightSensorPin the pin of the light sensor.
     * @param lightPin the pin of the light.
    */
    RoomSensorBoard(int pirPin, int lightSensorPin, int lightPin);

    /**
     * Sample presence.
    */
    void samplePresence();

    /**
     * Sample light level.
    */
    void sampleLightLevel();

    /**
     * Check if presence is detected.
     * @return true if presence is detected, false otherwise.
    */
    bool isPresenceDetected();

    /**
     * Get the light level.
     * @return the light level.
    */
    double getLightLevel();

    /**
     * Turn the sensor-board light system off.
    */
    void turnLightOff();

    /**
     * Turn the sensor-board light system on.
    */
    void turnLightOn();
};

#endif
