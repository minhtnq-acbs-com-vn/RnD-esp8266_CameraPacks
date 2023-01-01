#include <Arduino.h>
#include "Headers/mqtt.h"
#include "Headers/static.h"
#include "Headers/wificustom.h"

void setup()
{
  // Init Serial console
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");

  // Init wifi and mqtt
  wifiConnect();
  setupMQTTConnection();

  // Setup pin mode
  dht.begin();
  servo180.attach(servo180Pin);
  servo360.attach(servo360Pin);
  resetServo("Servo180", 0);
  resetServo("Servo360", 90);
  pinMode(lightSensor, INPUT);
  pinMode(soundSensor, INPUT);
}

void loop()
{
  if (!client.connected())
  {
    mqttReconnect();
  }
  client.loop();
  wifiCheck();
}