#ifndef __PIR__
#define __PIR__


/**
 * Class representing a simple pir.
*/
class Pir {
private:
    int pin;
    bool detected;

public:
    /**
     * Create a new pir with the given pin.
     * @param pin the pin number.
    */
    Pir(int pin);

    /**
     * Sample presence.
    */
    void detectPresence();

    /**
     * Check if movement is detected or not.
     * @return true if movement is detected, false otherwise.
    */
    bool isDetected();

    /**
     * Calibrate the pir.
    */
    void calibrate();
};

#endif
