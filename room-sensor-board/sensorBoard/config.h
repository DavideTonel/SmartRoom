#ifndef __CONFIG__
#define __CONFIG__


/* pin configuration */
#define PIR_PIN 5
#define LIGHT_SENSOR_PIN 6
#define LED_PIN 7

/* wifi network info */
const char* ssid = "A50";
const char* password = "javacomp";

/* MQTT server address */
const char* mqtt_server = "broker.mqtt-dashboard.com";

/* MQTT topic */
const char* presenceTopic = "sensorBoard/presenceDetected";
const char* lightLevelTopic = "sensorBoard/lightLevel";

/* Task Periods */
const int lightControlTaskPeriod = 200;
const int lightLevelSamplingTaskPeriod = 100;
const int presenceSamplingTaskPeriod = 100;

/* MQTT */
const int mqttUpdateRate = 700;

#endif
