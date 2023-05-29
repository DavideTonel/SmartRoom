#ifndef __ROLLERBLINDCONTROL_TASK__
#define __ROLLERBLINDCONTROL_TASK__

#include "core/Task.h"
#include "model/SmartRoom.h"
#include "model/TimeService.h"
#include "model/RollerBlind.h"


/**
 * Class representing a task used to control the smart room rollerblind system.
*/
class RollerBlindControlTask: public Task {
private:  
    void setState(int state);
    long elapsedTimeInState();
    enum { CLOSED, OPEN, MANUAL, MOVING} state, finalState;
    long stateTimestamp;
    SmartRoom* room;
    TimeService* timeService;
    RollerBlind* rollerblind;

public:
    /**
    * Create a rollerblind control task for the given room with the given time service.
    * @param room the room.
    * @param timeService the time service.
    */
    RollerBlindControlTask(SmartRoom* room, TimeService* timeService);

    /**
    * Execute the task.
    */
    void tick();
};

#endif
