#include "../Headers/static.h"

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
  Serial.println(result);
  String result_as_string = tempID + String(result, 1);
  publishFlag(topicCameraPacksDevice, result_as_string);
  publishConfirm(typeOfConfirmation_Temp);
}

float readLightState()
{
  return digitalRead(lightSensor);
}

void responseLightState()
{
  int result = readLightState();
  String result_as_string = lightID + String(result);
  publishFlag(topicCameraPacksDevice, result_as_string);
  publishConfirm(typeOfConfirmation_LightState);
}

void resetServo()
{
  servo180.write(servo180DefaultDegree);
  servo360.write(servo360DefaultDegree);
}

void swingServo(String servoID, int degree)
{
  if (servoID == "Servo180")
    servo180.write(degree);
  if (servoID == "Servo360")
    servo360.write(degree);
}

void servoHandler(String request)
{
  int pos = request.indexOf(":");
  String servoID = request.substring(7, pos);
  int servoDegree = request.substring(pos + 1).toInt();
  swingServo(servoID, servoDegree);
  publishConfirm(typeOfConfirmation_Servo);
}

void publishConfirm(String type)
{
  if (type == typeOfConfirmation_LightState)
    publishFlag(topicCameraPacksACK, deviceLightStateConfirmed);
  if (type == typeOfConfirmation_Temp)
    publishFlag(topicCameraPacksACK, deviceTempConfirmed);
  if (type == typeOfConfirmation_Servo)
    publishFlag(topicCameraPacksACK, deviceServoConfirmed);
}