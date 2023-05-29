#include <Arduino.h>
#include "config.h"
#include "core/Scheduler.h"
#include "model/SmartRoom.h"
#include "model/TimeService.h"
#include "core/Task.h"
#include "tasks/RollerBlindControlTask.h"
#include "tasks/SerialComTask.h"
#include "tasks/LightControlTask.h"
#include "tasks/BluetoothComTask.h"


Scheduler scheduler;
SmartRoom* room;
TimeService* timeService;


void setup() {
  scheduler.init(100);

  room = new SmartRoom(ROLLERBLIND_PIN, LED_PIN);
  timeService = new TimeService();

  Task* rollerblindControlTask = new RollerBlindControlTask(room, timeService);
  rollerblindControlTask->init(200);

  Task* serialComTask = new SerialComTask(room, timeService);
  serialComTask->init(500);

  Task* lightControlTask = new LightControlTask(room);
  lightControlTask->init(200);

  Task* bluetoothComTask = new BluetoothComTask(room, timeService);
  bluetoothComTask->init(500);

  scheduler.addTask(serialComTask);
  scheduler.addTask(bluetoothComTask);
  scheduler.addTask(rollerblindControlTask);
  scheduler.addTask(lightControlTask);
}

void loop() {
  scheduler.schedule();
}
