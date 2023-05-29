#include "SerialComTask.h"
#include "ArduinoJson.h"


SerialComTask::SerialComTask(SmartRoom* room, TimeService* time) {
    this->channel = new SerialCommunication();
    this->channel->init();
    
    this->room = room;
    this->time = time;
}

void SerialComTask::tick() {
    if (channel->isMsgAvailable()) {
        Msg* msg = channel->receiveMsg();
        String content = msg->getcontent();
        delete(msg);
        handleContent(content);
    }
    notify();
}

void SerialComTask::handleContent(String content) {
    if (room->isAutoMode() && content.equals("chmod MANUAL_SERIAL")) {
        room->setSerialMode();
    } else if (room->isSerialMode() && content.equals("chmod AUTO")) {
        room->setAutoMode();
    } else {
        DynamicJsonDocument json(128);
        DeserializationError error = deserializeJson(json, content);
        if (!error) {
            if (json.containsKey("presenceDetected")) {
                int presenceDetected = json["presenceDetected"].as<int>() ? true : false;
                room->setPresenceDetected(presenceDetected);
            }

            if (json.containsKey("lightLevel")) {
                double lightLevel = json["lightLevel"].as<double>();
                room->setLightLevel(lightLevel);
            }

            if (json.containsKey("hour")) {
                int hour = json["hour"].as<int>();
                time->setHour(hour);
            }

            // input from Serial
            if (room->isSerialMode()) {
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
}

void SerialComTask::notify() {
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
