#include "TimeService.h"


TimeService::TimeService() {
    this->hours = 0;
}

int TimeService::getHour() {
    return hours;
}

void TimeService::setHour(int hours) {
    this->hours = hours;
}
