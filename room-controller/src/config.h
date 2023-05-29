#ifndef __CONFIG__
#define __CONFIG__


// Scheduler configuration
#define MAX_TASKS 50

// Pin configuration
#define ROLLERBLIND_PIN 4
#define LED_PIN 7
#define RX_PIN 12
#define TX_PIN 13

// Rollerblind configuration
#define MAX_OPEN_PERCENTAGE 100
#define MIN_OPEN_PERCENTAGE 0

// RollerBlindControlTask configuration
#define ROOM_OPEN_HOUR 8
#define ROOM_CLOSE_HOUR 19
#define ROLLERBLIND_MOVING_DELAY 1000

// LightControlTask configuration
#define MIN_LIGHT_LEVEL 3

#endif
