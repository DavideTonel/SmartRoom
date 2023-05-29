#ifndef __BLUETOOTH_COMMUNICATION__
#define __BLUETOOTH_COMMUNICATION__

#include <Arduino.h>
#include "Communication.h"
#include "SoftwareSerial.h"


/**
 * Class representing a bluetooth communication.
*/
class BluetoothCommunication : public Communication {
private:
    SoftwareSerial* channel;
    Msg* currentMsg;
    bool availableMsg;
    String content;

public:
    /**
     * Create a new bluetooth communication.
     * @param rxPin number of the RX pin (to be connected to TXD of BT module).
     * @param txPin number of the TX pin (to be connected to RXD of BT module).
    */
    BluetoothCommunication(int rxPin, int txPin);

    /**
     * Initializes the bluetooth communication.
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
