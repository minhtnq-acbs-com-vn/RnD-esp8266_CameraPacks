#pragma once

String setupString(String options);

const String deviceName = "espInCameraPacks";
const String roomName = "room1";
const String packetACK = "ACK";
const String serverName = "server";
// Setup topic
// From device
const char *topicCameraPacksDevice = setupString("device").c_str();
const char *topicCameraPacksACK = setupString("ack").c_str();
// To device
const char *topicCameraPacksServer = setupString("server").c_str();

String setupString(String options)
{
    String temp = deviceName + "/" + roomName;
    if (options == "device") return temp;
    else if (options == "ack") return temp += "/" + packetACK;
    else if (options == "server") return temp += "/" + serverName;
    else return options;
}