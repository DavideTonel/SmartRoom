#ifndef __LIGHTSENSOR__
#define __LIGHTSENSOR__


/**
 * Interface representing a simple light sensor.
*/
class LightSensor {
public:
  /**
   * Get the light level.
   * @return the light level.
  */
  virtual double getLightLevel() = 0;
};

#endif
