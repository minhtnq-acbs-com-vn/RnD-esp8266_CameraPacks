#pragma once

// Setup MQTT
const char *mqttServer = "192.168.19.98";
const char *mqttUsername = "pi";
const char *mqttPassword = "qwertasdfg";
const int port = 1885;

const char *mqttClientID = String(ESP.getChipId()).c_str();
