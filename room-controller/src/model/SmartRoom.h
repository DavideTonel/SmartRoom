#ifndef __SMARTROOM__
#define __SMARTROOM__

#include "RollerBlind.h"
#include "devices/Light.h"


/**
 * Class representing the smart room.
*/
class SmartRoom {
private:
    RollerBlind* rollerblind;
    Light* light;
    enum { AUTO, MANUAL_SERIAL, MANUAL_BT } controlMode;

    // sensor-board data
    bool presenceDetected;
    double lightLevel;

    // remote input
    int remoteBlindOpenPercentage;
    bool remoteLightOn;

public:
    /**
     * Create a new smart room with the given rollerblind pin and light pin.
     * @param rollerblindServoPin the rollerblind pin.
     * @param lightPin the light pin.
    */
    SmartRoom(int rollerblindServoPin, int lightPin);

    /**
     * Get the rollerblind.
     * @return the rollerblind.
    */
    RollerBlind* getRollerBlinds();

    /**
     * Get the light.
     * @return the light.
    */
    Light* getLight();

    /**
     * Check if presence is detected inside the room.
     * @return true if presence is detected, false otherwise.
    */
    bool isPresenceDetected();

    /**
     * Get the light level inside the room.
     * @return the light level inside the room.
    */
    double getLightLevel();

    /**
     * Set presence in room.
     * @param value presence in room or not.
    */
    void setPresenceDetected(bool value);

    /**
     * Set light level inside the room.
     * @param value the light level inside the room.
    */
    void setLightLevel(double value);

    /**
     * Check if the room is in auto control mode.
     * @return true if the room is in auto control mode, false otherwise.
    */
    bool isAutoMode();

    /**
     * Check if the room is in serial control mode.
     * @return true if the room is in serial control mode, false otherwise.
    */
    bool isSerialMode();

    /**
     * Check if the room is in bluetooth control mode.
     * @return true if the room is in bluetooth control mode, false otherwise.
    */
    bool isBluetoothMode();

    /**
     * Set te room in auto control mode.
    */
    void setAutoMode();

    /**
     * Set te room in serial control mode.
    */
    void setSerialMode();

    /**
     * Set te room in bluetooth control mode.
    */
    void setBluetoothMode();

    /**
     * Set rollerblind open percentage from remote.
     * @param value the rollerblind open percentage to set.
    */
    void setRemoteBlindOpenPercentage(int value);

    /**
     * Get rollerblind open percentage from remote.
     * @return the rollerblind open percentage from remote.
    */
    int getRemoteBlindOpenPercentage();

    /**
     * Set light value from remote.
     * @param value the light value to set from remote.
    */
    void setRemoteLightValue(int value);

    /**
     * Get light value from remote.
     * @return true if the light from remote is on, false otherwise.
    */
    bool getRemoteLightValue();
};

#endif
