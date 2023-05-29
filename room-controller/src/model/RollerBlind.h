#ifndef __ROLLERBLIND__
#define __ROLLERBLIND__

#include "devices/ServoMotor.h"


/**
 * Class representing a controllable rollerblind,
*/
class RollerBlind {
private:
    ServoMotor* motor;
    int openPercentage;

public:
    /**
     * Creates a new rollerblind with the given pin.
     * @param servoPin the pin of the servomotor.
    */
    RollerBlind(int servoPin);

    /**
     * Turn on the rollerblind.
    */
    void on();

    /**
     * Turn off the rollerblind.
    */
    void off();

    /**
     * Full roll the rollerblind.
    */
    void fullRoll();

    /**
     * Full unroll the rollerblind.
    */
    void fullUnroll();

    /**
     * Roll the rollerblind of the given open percentage.
     * @param value the rollerblind open percentage.
    */
    void roll(int value);

    /**
     * Get the rollerblind open percentage.
     * @return the rollerblind open percentage
    */
    int getOpenPercentage();
};

#endif
