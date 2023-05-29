#ifndef __COMMUNICATION__
#define __COMMUNICATION__

#include "Msg.h"


/**
 * Interface representing a communication.
*/
class Communication {
public:
    /**
     * Initializes the bluetooth communication.
    */
    virtual void init() = 0;

    /**
     * Check if a message is available.
     * @return true if a message is available, false otherwise.
    */
    virtual bool isMsgAvailable() = 0;

    /**
     * Receive the message.
     * @return the message.
    */
    virtual Msg* receiveMsg() = 0;

    /**
     * Send the message.
     * @param msg the message to send.
    */
    virtual void sendMsg(Msg msg) = 0;
};

#endif
