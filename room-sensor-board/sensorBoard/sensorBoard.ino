#include "config.h"
#include "RoomSensorBoard.h"
#include "LightLevelSamplingTask.h"
#include "PresenceSamplingTask.h"
#include "LightControlTask.h"
#include <WiFi.h>
#include <PubSubClient.h>

#define MSG_BUFFER_SIZE  50


/* MQTT client management */
WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsgTime = 0;
char msg[MSG_BUFFER_SIZE];

RoomSensorBoard* sensorBoard;
PresenceSamplingTask* presenceTask;
LightLevelSamplingTask* lightLevelTask;
LightControlTask* lightControlTask;


void setup_wifi() {
  delay(10);
  Serial.println(String("Connecting to ") + ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Create a random client ID
    String clientId = String("client-")+String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


TaskHandle_t Task1;
void Task1code(void * parameter) {
  for (;;) {
    presenceTask->tick();
    delay(presenceSamplingTaskPeriod);
  }
}

TaskHandle_t Task2;
void Task2code(void * parameter) {
  for (;;) {
    lightLevelTask->tick();
    delay(lightLevelSamplingTaskPeriod);
  }
}

TaskHandle_t Task3;
void Task3code(void * parameter) {
  for (;;) {
    lightControlTask->tick();
    delay(lightControlTaskPeriod);
  }
}


void setup() {
  Serial.begin(115200);

  sensorBoard = new RoomSensorBoard(PIR_PIN, LIGHT_SENSOR_PIN, LED_PIN);

  presenceTask = new PresenceSamplingTask(sensorBoard);
  lightLevelTask = new LightLevelSamplingTask(sensorBoard);
  lightControlTask = new LightControlTask(sensorBoard);

  // presenceTask
  xTaskCreatePinnedToCore(Task1code,"Task1",10000,NULL,1,&Task1,1);
  // lightLevelTask
  xTaskCreatePinnedToCore(Task2code,"Task2",10000,NULL,1,&Task2,1);
  // lightTask
  xTaskCreatePinnedToCore(Task3code,"Task3",10000,NULL,1,&Task3,1);

  setup_wifi();
  randomSeed(micros());
  client.setServer(mqtt_server, 1883);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();


  unsigned long now = millis();
  if (now - lastMsgTime > mqttUpdateRate) {
    lastMsgTime = now;

    snprintf (msg, MSG_BUFFER_SIZE, "%.2f", sensorBoard->getLightLevel());
    client.publish(lightLevelTopic, msg);

    snprintf (msg, MSG_BUFFER_SIZE, "%d", sensorBoard->isPresenceDetected() ? 1 : 0);
    client.publish(presenceTopic, msg);
  }
}
