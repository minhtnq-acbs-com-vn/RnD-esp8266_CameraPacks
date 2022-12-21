#pragma once

// Setup MQTT
const char *mqttServer = "159.223.85.198";
const int port = 1883;

const char *espID = String(ESP.getChipId()).c_str();
const char *deviceID = "espInCameraPacks";

const char *mqttClientID = espID + *deviceID;
const char *mqttUsername = "cloud";
const char *mqttPassword = "R&D_2022_Ocean";