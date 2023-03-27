#include "../Headers/api.h"

void sentDeviceInfo()
{
    HTTPClient http;
    String payload = "";
    http.begin(secureClient, apiHost);
    String json = packToJson();
    Serial.println(json);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("userid", userID);
    http.addHeader("system", systemKey);
    int httpCode = http.POST(json);
    Serial.println(http.errorToString(httpCode));
    while (httpCode != 200)
    {
        http.end();
        delay(10000);
        http.begin(secureClient, apiHost);
        String json = packToJson();
        http.addHeader("Content-Type", "application/json");
        http.addHeader("userid", userID);
        http.addHeader("system", systemKey);
        int httpCode = http.POST(json);
        Serial.println(http.errorToString(httpCode));
        if (httpCode == 200)
            break;
    }

    // Check the returning code
    payload = http.getString(); // Get the request response payload
    Serial.println(payload);    // Print the response payload

    http.end();
}

String getDeviceInfo()
{
    HTTPClient http;
    String payload = "";
    http.begin(secureClient, apiQuery);
    http.addHeader("userid", userID);
    http.addHeader("system", systemKey);

    int httpCode = http.GET();
    Serial.println(http.errorToString(httpCode));
    while (httpCode != 200)
    {
        http.end();
        delay(10000);
        http.begin(secureClient, apiQuery);
        http.addHeader("userid", userID);
        http.addHeader("system", systemKey);
        int httpCode = http.GET();
        Serial.println(http.errorToString(httpCode));
        if (httpCode == 200)
            break;
    }
    // Check the returning code
    payload = http.getString(); // Get the request response payload

    http.end();
    return payload;
}

void setupDeviceConfig()
{
    String payload = getDeviceInfo();
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, payload);
    if (error)
        Serial.println(error.f_str());
    else
    {
        setupPacketConfig(doc);
        setupPin(doc);
    }
}

void setupPacketConfig(DynamicJsonDocument doc)
{
    deviceLightStateConfirmed = doc["ack"]["lightState"].as<String>();
    deviceTempConfirmed = doc["ack"]["temp"].as<String>();
    deviceServoConfirmed = doc["ack"]["servo"].as<String>();
    serverRequestTemp = doc["request"]["temp"].as<String>();
    serverRequestLightState = doc["request"]["lightState"].as<String>();
    serverRequestServo = doc["request"]["servo"].as<String>();
    requestAPI = doc["request"]["api"].as<String>();
}

void setupPin(DynamicJsonDocument doc)
{
    dhtSensor = doc["pin"]["dht"].as<int>();
    lightSensor = doc["pin"]["lightState"].as<int>();
    servo360Pin = doc["pin"]["servo360"].as<int>();
    servo180Pin = doc["pin"]["servo180"].as<int>();
}

void printChanges(String option)
{

    for (auto &element : ack)
    {
        Serial.println(element);
    }
    for (auto &element : request)
    {
        Serial.println(element);
    }

    for (auto &element : pin)
    {
        Serial.println(element);
    }
}