#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include "ServoMotor.h"
#include <arduino.h>
#include "ServoTimer2.h"


/**
 * Class representing a simple servomotor.
*/
class ServoMotorImpl: public ServoMotor {
private:
    int pin; 
    ServoTimer2 motor;

public:
    /**
     * Create a new servomotor with the given pin.
     * @param pin the pin of the servomotor.
    */
    ServoMotorImpl(int pin);

    /**
     * Turn on the servomotor.
    */
    void on();

    /**
     * Turn off the servomotor.
    */
    void off();

    /**
     * Move the servomotor of the given angle.
     * @param angle the angle to set.
    */
    void setPosition(int angle);
};

#endif
