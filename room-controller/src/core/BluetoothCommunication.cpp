#include "BluetoothCommunication.h"


BluetoothCommunication::BluetoothCommunication(int rxPin, int txPin) {
    this->channel = new SoftwareSerial(rxPin, txPin);
}

void BluetoothCommunication::init() {
    channel->begin(9600);
    content.reserve(256);
    content = "";
    currentMsg = NULL;
    availableMsg = false;
}

bool BluetoothCommunication::isMsgAvailable() {
    while (channel->available()) {
        char ch = (char) channel->read();
        if (ch == '\n') {
            currentMsg = new Msg(content);
            availableMsg = true;
            return true;
        } else {
            content += ch;
        }
    }
    return false;
}

Msg* BluetoothCommunication::receiveMsg() {
    if (availableMsg) {
        Msg* msg = currentMsg;
        availableMsg = false;
        currentMsg = NULL;
        content = "";
        return msg;
    }
    return NULL;
}

void BluetoothCommunication::sendMsg(Msg msg) {
    channel->println(msg.getcontent());
}
