#ifndef __PRESENCESAMPLINGTASK__
#define __PRESENCESAMPLINGTASK__

#include "Task.h"
#include "RoomSensorBoard.h"

/**
 * Class representing a task that samples the movement.
*/
class PresenceSamplingTask : public Task {
private:
    RoomSensorBoard* sensorBoard;
    
public:
    /**
     * Create a new presence sampling task for the given sensor-board.
     * @param sensorBoard the sensor-board.
    */
    PresenceSamplingTask(RoomSensorBoard* sensorBoard);

    /**
     * Execute the task.
    */
    void tick();
};

#endif
