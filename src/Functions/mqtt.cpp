#include "../Headers/mqtt.h"

void setupMQTTConnection()
{
    client.setServer(mqttServer, port);
    client.setCallback(callback);
}

void callback(char *topic, byte *message, unsigned int length)
{
    Serial.println(topic);
    String strMsg;
    for (uint32_t i = 0; i < length; i++)
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