#ifndef __BLUETOOTHCOMTASK__
#define __BLUETOOTHCOMTASK__

#include "core/Task.h"
#include "core/BluetoothCommunication.h"
#include "ArduinoJson.h"
#include "../model/SmartRoom.h"
#include "../model/TimeService.h"


/**
 * Class representing a task used to control the smart room bluetooth communication.
*/
class BluetoothComTask : public Task {
private:
    SmartRoom* room;
    TimeService* time;
    BluetoothCommunication* channel;

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
     * Create a bluetooth communication control task for the given room with the given time service.
     * @param room the room.
     * @param timeService the time service.
    */
    BluetoothComTask(SmartRoom* room, TimeService* time);

    /**
     * Execute the task.
    */
    void tick();
};

#endif
