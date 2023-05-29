#ifndef __SERIAL_COMMUNICATION__
#define __SERIAL_COMMUNICATION__

#include "Communication.h"


/**
 * Class representing a serial communication.
*/
class SerialCommunication : public Communication {
private:
    Msg* currentMsg;
    bool availableMsg;
    String content;

public:
    /**
     * Initializes the serial communication.
    */
    void init();

    /**
     * Check if a message is available.
     * @return true if a message is available, false otherwise.
    */
    bool isMsgAvailable();

    /**
     * Receive the message.
     * @return the message.
    */
    Msg* receiveMsg();

    /**
     * Send the message.
     * @param msg the message to send.
    */
    void sendMsg(Msg msg);
};

#endif
