#include <Arduino.h>
#include "Headers/mqtt.h"
#include "Headers/static.h"
#include "Headers/wificustom.h"

void setup()
{
  // Init Serial console
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");
  delay(500);

  // Setup pin mode
  servo180.attach(servo180Pin, 500, 2500);
  servo360.attach(servo360Pin, 500, 2500);
  resetServo();
  pinMode(lightSensor, INPUT);
  dht.begin();

  // Init wifi and mqtt
  wifiConnect();
  setupMQTTConnection();
  sentDeviceInfo();
  setupDeviceConfig();
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