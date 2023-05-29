#ifndef __LIGHT__
#define __LIGHT__


/**
 * Interface representing a simple light.
*/
class Light {
public:
    /**
     * Switch on the light.
    */
    virtual void switchOn() = 0;

    /**
     * Switch off the light.
    */
    virtual void switchOff() = 0;

    /**
     * Return if the light is on or off.
     * @return true if the light is on otherwise false.
    */
    virtual bool isOn() = 0;   
};

#endif
