#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__


/**
 * Inteface representing a simple servomotor.
*/
class ServoMotor {
public:
    /**
     * Turn on the servomotor.
    */
    virtual void on() = 0;

    /**
     * Turn off the servomotor.
    */
    virtual void off() = 0;

    /**
     * Move the servomotor of the given angle.
     * @param angle the angle to set.
    */
    virtual void setPosition(int angle) = 0;
};

#endif
