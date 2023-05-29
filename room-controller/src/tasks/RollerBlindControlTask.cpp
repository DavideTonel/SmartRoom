#include "Arduino.h"
#include "tasks/RollerBlindControlTask.h"
#include "config.h"


RollerBlindControlTask::RollerBlindControlTask(SmartRoom* room, TimeService* timeService) {
    this->room = room;
    this->timeService = timeService;
    this->rollerblind = room->getRollerBlinds();
    setState(CLOSED);
    finalState = CLOSED;
}

void RollerBlindControlTask::tick() {
    int hour = timeService->getHour();
    switch (state) {
    case CLOSED: {
        if (room->isAutoMode()) {
            if (room->isPresenceDetected() && (hour >= ROOM_OPEN_HOUR && hour < ROOM_CLOSE_HOUR)) {
                rollerblind->on();
                rollerblind->fullRoll();
                state = OPEN;
                finalState = state;
                setState(MOVING);
            }
        } else {
            setState(MANUAL);
        }
        break;
    }

    case OPEN: {
        if (room->isAutoMode()) {
            if (!room->isPresenceDetected() && (hour < ROOM_OPEN_HOUR || hour >= ROOM_CLOSE_HOUR)) {
                rollerblind->on();
                rollerblind->fullUnroll();
                state = CLOSED;
                finalState = state;
                setState(MOVING);
            }
        } else {
            setState(MANUAL);
        }
        break;
    }

    case MANUAL: {
        if (!room->isAutoMode()) {
            rollerblind->on();
            rollerblind->roll(room->getRemoteBlindOpenPercentage());
            finalState = state;
            setState(MOVING);
        } else {
            if (room->isPresenceDetected() && (hour >= ROOM_OPEN_HOUR || hour < ROOM_CLOSE_HOUR)) {
                rollerblind->on();
                rollerblind->fullRoll();
                state = OPEN;
                finalState = state;
                setState(MOVING);
            } else {
                rollerblind->on();
                rollerblind->fullUnroll();
                state = CLOSED;
                finalState = state;
                setState(MOVING);
            }
        }
        break;
    }

    case MOVING: {
        if (elapsedTimeInState() >= ROLLERBLIND_MOVING_DELAY) {
            setState(finalState);
            rollerblind->off();
        }
        break;
    }

    default: {
        break;
    }
    }
}

void RollerBlindControlTask::setState(int s){
    state = s;
    stateTimestamp = millis();
}

long RollerBlindControlTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}
