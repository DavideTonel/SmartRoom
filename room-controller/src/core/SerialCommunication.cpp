#include <Arduino.h>
#include "SerialCommunication.h"


void SerialCommunication::init() {
    Serial.begin(9600);
    while (!Serial) {};
    content.reserve(256);
    content = "";
    currentMsg = NULL;
    availableMsg = false;
}

bool SerialCommunication::isMsgAvailable() {
    while (Serial.available()) {
        char ch = (char) Serial.read();
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

Msg* SerialCommunication::receiveMsg() {
    if (availableMsg) {
        Msg* msg = currentMsg;
        availableMsg = false;
        currentMsg = NULL;
        content = "";
        return msg;
    }
    return NULL;
}

void SerialCommunication::sendMsg(Msg msg) {
    Serial.println(msg.getcontent());
}
