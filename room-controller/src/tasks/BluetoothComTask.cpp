#include "BluetoothComTask.h"
#include "config.h"


BluetoothComTask::BluetoothComTask(SmartRoom* room, TimeService* time) {
    channel = new BluetoothCommunication(RX_PIN, TX_PIN);
    channel->init();
    this->room = room;
    this->time = time;
}

void BluetoothComTask::tick() {
    if (channel->isMsgAvailable()) {
        Msg* msg = channel->receiveMsg();
        String content = msg->getcontent();
        delete(msg);
        handleContent(content);
    } else {
        notify();
    }
}

void BluetoothComTask::handleContent(String content) {
    if (room->isAutoMode() && content.equals("chmod MANUAL_BT")) {
        room->setBluetoothMode();
    } else if (room->isBluetoothMode() && content.equals("chmod AUTO")) {
        room->setAutoMode();
    } else if (room->isBluetoothMode()) {
        DynamicJsonDocument json(128);
        DeserializationError error = deserializeJson(json, content);
        if (!error) {
            if (json.containsKey("remoteBlindOpenPercentage")) {
                int remoteBlindOpenPercentage = json["remoteBlindOpenPercentage"].as<int>();
                room->setRemoteBlindOpenPercentage(remoteBlindOpenPercentage);
            }

            if (json.containsKey("remoteLightOn")) {
                int remoteLightOn = json["remoteLightOn"].as<int>() == 1 ? true : false;
                room->setRemoteLightValue(remoteLightOn);
            }
        }
    }
}

void BluetoothComTask::notify() {
    int blindOpenPercentage = room->getRollerBlinds()->getOpenPercentage();
    int lightOn = room->getLight()->isOn() ? 1 : 0;
    String controlMode = "";
    if (room->isAutoMode()) {
        controlMode = "AUTO";
    } else if (room->isSerialMode()) {
        controlMode = "MANUAL_SERIAL";
    } else if (room->isBluetoothMode()) {
        controlMode = "MANUAL_BT";
    }

    String updateString = "{";
    updateString += "\"blindOpenPercentage\": " + String(blindOpenPercentage) + ",";
    updateString += "\"lightOn\": " + String(lightOn) + ",";
    updateString += "\"controlMode\": \"" + controlMode + "\"";
    updateString += "}";
    channel->sendMsg(Msg(updateString));
}
