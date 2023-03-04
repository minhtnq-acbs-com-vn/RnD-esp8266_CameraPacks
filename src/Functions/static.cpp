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
    if (servoID == "Servo360")
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
    servo180.write(degree);
    // for (int i = 0; i <= degree; i++)
    // {
    //   servo180.write(i);
    // }
    // delay(1000);
    // resetServo("Servo180", degree);
  }
  if (servoID == "Servo360")
  {
    for (int i = 0; i <= degree; i++)
    {
      servo360.write(i);
    }
    delay(1000);
    resetServo("Servo360", degree);
  }
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