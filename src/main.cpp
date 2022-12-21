#include <Arduino.h>
#include <Headers/Command_Variable/packet.h>
#include <Headers/GPIO/pin.h>
#include <Headers/Network/client.h>
#include <Headers/Network/mqtt.h>
#include <Headers/Network/topic.h>

// Function declaration
// STATIC
void publishFlag(const char *topic, const String flag);
float readTemp();
void responseTemp();
float readLightState();
void responseLightState();
int readSoundState();
void responseSoundState();
void resetServo(String servoID);
void swingServo(String servoID, int degree);
void publishConfirm(String type);
// NETWORK
void wifiConnect();
void mqttReconnect();
void wifiCheck();
void failedReconnect();
// DATA HANDLING
void callback(char *topic, byte *message, unsigned int length);

void setup()
{
  // Init Serial console
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");

  // Init wifi and mqtt
  wifiConnect();
  client.setServer(mqttServer, port);
  client.setCallback(callback);

  // Setup pin mode
  dht.begin();
  servo180.attach(servo180Pin);
  servo360.attach(servo360Pin);
  resetServo("Servo180");
  resetServo("Servo360");
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

/////////////STATIC FUNCTION/////////////
// Use to publish a string to a specific topic
void publishFlag(const char *topic, const String flag)
{
  client.publish(topic, flag.c_str());
}

// Return float room temperature
float readTemp()
{
  return dht.readTemperature();
}

// Convert float temp to string temp and publish to a specific topic
void responseTemp()
{
  float result = readTemp();
  String result_as_string = tempID + String(result, 1);
  publishFlag(topicCameraPacksDevice, result_as_string);
}

float readLightState()
{
  return analogRead(lightSensor);
}

void responseLightState()
{
  float result = readLightState();
  String result_as_string = lightID + String(result, 1);
  publishFlag(topicCameraPacksDevice, result_as_string);
}

int readSoundState()
{
  return digitalRead(soundSensor);
}

void responseSoundState()
{
  int result = readSoundState();
  String result_as_string = soundID + String(result, 1);
  publishFlag(topicCameraPacksDevice, result_as_string);
}

void resetServo(String servoID)
{
  if (servoID == "Servo180")
    servo180.write(defaultDegree);
  else if (servoID == "Servo360")
    servo360.write(defaultDegree);
  delay(1000);
}

void swingServo(String servoID, int degree)
{
  if (servoID == "Servo180")
  {
    servo180.write(degree);
    delay(1000);
    resetServo("Servo180");
  }
  else if (servoID == "Servo360")
  {
    servo360.write(degree);
    delay(1000);
    resetServo("Servo360");
  }
}

void publishConfirm(String type)
{
  if (type == typeOfConfirmation_LightState)
    publishFlag(topicCameraPacksACK, deviceLightStateConfirmed);
  else if (type == typeOfConfirmation_Temp)
    publishFlag(topicCameraPacksACK, deviceTempConfirmed);
  else if (type == typeOfConfirmation_SoundState)
    publishFlag(topicCameraPacksACK, deviceSoundStateConfirmed);
  else if (type == typeOfConfirmation_Servo)
    publishFlag(topicCameraPacksACK, deviceServoConfirmed);
}
/////////////STATIC FUNCTION/////////////

/////////////NETWORK FUNCTION/////////////
// Connect wifi
void wifiConnect()
{
  wifiManager.setTimeout(180);

  if (!wifiManager.autoConnect("AutoConnectAP"))
  {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  Serial.println("connected...yeey :)");
}

// Connect to mqtt broker and subscribe to specific topic(s)
void mqttReconnect()
{
  while (!client.connected())
  {
    Serial.println("Attemping MQTT connection...");
    if (client.connect(mqttClientID, mqttUsername, mqttPassword))
    {
      Serial.println("Connected");

      //***Subscribe all topic you need***
      client.subscribe(topicCameraPacksServer);
    }
    else
    {
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

void wifiCheck()
{
  uint32_t notConnectedCounter = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    notConnectedCounter++;
    if (notConnectedCounter > 300)
    { // Reset board if not connected after 15s
      Serial.println("Resetting due to Wifi not connecting...");
      WiFi.reconnect();
      // failedReconnect();
    }
  }
}

void failedReconnect()
{
  delay(10000);                  // let esp take time reconnect
  for (int i = 0; i < 6000; i++) // wait for 5 minutes before reset esp
  {
    delay(500);
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    ESP.restart();
  }
}
/////////////NETWORK FUNCTION/////////////

/////////////DATA HANDLING FUNCTION/////////////
// Handle mqtt packet here
void callback(char *topic, byte *message, unsigned int length)
{
  Serial.println(topic);
  String strMsg;
  for (unsigned int i = 0; i < length; i++)
  {
    strMsg += (char)message[i];
  }
  Serial.println(strMsg);

  if (strMsg == serverRequestTemp)
  {
    responseTemp();
    publishConfirm(typeOfConfirmation_Temp);
  }
  else if (strMsg == serverRequestLightState)
  {
    responseLightState();
    publishConfirm(typeOfConfirmation_LightState);
  }
  else if (strMsg == serverRequestSoundState)
  {
    responseSoundState();
    publishConfirm(typeOfConfirmation_SoundState);
  }
  else if (strMsg.startsWith("Servo", 7))
  {
    int pos = strMsg.indexOf(":");
    String servoID = strMsg.substring(7, pos);
    int servoDegree = strMsg.substring(pos + 1).toInt();
    swingServo(servoID, servoDegree);
    publishConfirm(typeOfConfirmation_Servo);
  }
}
/////////////DATA HANDLING FUNCTION/////////////