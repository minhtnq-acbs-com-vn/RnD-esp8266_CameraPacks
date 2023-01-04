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

void resetServo(String servoID, int degree)
{
  if (degree == 0)
  {
    servo180.write(defaultDegree);
    servo360.write(defaultDegree);
  }
  else
  {
    if (servoID == "Servo180")
    {
      for (int i = degree; i >= defaultDegree; i--)
      {
        servo180.write(i);
      }
    }
    else if (servoID == "Servo360")
    {
      for (int i = degree; i >= defaultDegree; i--)
      {
        servo360.write(i);
      }
    }
  }
  delay(1000);
}

void swingServo(String servoID, int degree)
{
  if (servoID == "Servo180")
  {
    for (int i = 0; i <= degree; i++)
    {
      servo180.write(i);
    }
    delay(1000);
    resetServo("Servo180", degree);
  }
  else if (servoID == "Servo360")
  {
    for (int i = 0; i <= degree; i++)
    {
      servo360.write(i);
    }
    delay(1000);
    resetServo("Servo360", degree);
  }
}

void publishConfirm(String type)
{
  if (type == typeOfConfirmation_LightState)
    publishFlag(topicCameraPacksACK, deviceLightStateConfirmed);
  else if (type == typeOfConfirmation_Temp)
    publishFlag(topicCameraPacksACK, deviceTempConfirmed);
  else if (type == typeOfConfirmation_Servo)
    publishFlag(topicCameraPacksACK, deviceServoConfirmed);
}