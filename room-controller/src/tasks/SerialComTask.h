#ifndef __SERIALCOMTASK__
#define __SERIALCOMTASK__

#include <Arduino.h>
#include "../core/Task.h"
#include "core/SerialCommunication.h"
#include "../model/SmartRoom.h"
#include "../model/TimeService.h"


/**
 * Class representing a task used to control the smart room serial communication.
*/
class SerialComTask : public Task {
private:
    SmartRoom* room;
    TimeService* time;
    SerialCommunication* channel;

    /**
     * Handle the content of the message.
     * @param content the content of the message.
    */
    void handleContent(String content);

    /**
     * Send to the remote device connected a status update message.
    */
    void notify();

public:
    /**
     * Create a serial communication control task for the given room with the given time service.
     * @param room the room.
     * @param timeService the time service.
    */
    SerialComTask(SmartRoom* room, TimeService* time);

    /**
     * Execute the task.
    */
    void tick();
};

#endif
