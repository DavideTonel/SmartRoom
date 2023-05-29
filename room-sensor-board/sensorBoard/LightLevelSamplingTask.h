#ifndef __LIGHTLEVELSAMPLINGTASK__
#define __LIGHTLEVELSAMPLINGTASK__

#include "Task.h"
#include "RoomSensorBoard.h"


/**
 * Class representing a task that samples the light level.
*/
class LightLevelSamplingTask : public Task {
private:
    RoomSensorBoard* sensorBoard;
    
public:
    /**
     * Create a new light level sampling task for the given sensor-board.
     * @param sensorBoard the sensor-board.
    */
    LightLevelSamplingTask(RoomSensorBoard* sensorBoard);

    /**
     * Execute the task.
    */
    void tick();
};

#endif
