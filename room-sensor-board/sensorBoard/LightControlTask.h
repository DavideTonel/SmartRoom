#ifndef __LIGHTCONTROL_TASK__
#define __LIGHTCONTROL_TASK__

#include "Task.h"
#include "RoomSensorBoard.h"


/**
 * Class representing a task used to control the sensor-board light system.
*/
class LightControlTask : public Task {
private:
    RoomSensorBoard* sensorBoard;
    enum LightState { OFF, ON } lightState;

public:
    /**
    * Create a light control task for the given sensor-board.
    * @param sensorBoard the sensor-board.
    */
    LightControlTask(RoomSensorBoard* sensorBoard);

    /**
    * Execute the task.
    */
    void tick();

    /**
    * Set light system on.
    */
    void setStateOn();

    /**
    * Set light system off.
    */
    void setStateOff();
};

#endif
