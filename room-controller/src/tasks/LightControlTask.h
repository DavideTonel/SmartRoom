#ifndef __LIGHTCONTROL_TASK__
#define __LIGHTCONTROL_TASK__

#include "core/Task.h"
#include "model/SmartRoom.h"
#include "model/TimeService.h"
#include "devices/Light.h"


/**
 * Class representing a task used to control the smart room light system.
*/
class LightControlTask : public Task {
private:
    SmartRoom* room;
    Light* light;
    enum { OFF, ON, MANUAL } state;

public:
    /**
     * Create a light control task for the given room.
     * @param room the room.
    */
    LightControlTask(SmartRoom* room);

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

    /**
     * Set light system controlled from remote.
    */
    void setStateControlled();
};

#endif
