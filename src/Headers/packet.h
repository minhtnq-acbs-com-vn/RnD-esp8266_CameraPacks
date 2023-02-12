#ifndef PACKET_H
#define PACKET_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "pin.h"
#include "topic.h"
#include "api.h"

// Setup string
inline String serverRequestTemp = "requestTemp";
inline String serverRequestLightState = "requestLightState";
inline String serverRequestServo = "requestServo";
inline String requestAPI = "requestAPI";

inline String lightID = "Light: ";
inline String tempID = "Temp: ";

inline String typeOfConfirmation_LightState = "light_state";
inline String typeOfConfirmation_Temp = "temp";
inline String typeOfConfirmation_Servo = "servo";

inline String deviceLightStateConfirmed = "deviceLightStateConfirmed";
inline String deviceTempConfirmed = "deviceTempConfirmed";
inline String deviceServoConfirmed = "deviceServoConfirmed";

inline int defaultDegree = 0;
inline int degree = 180;

inline String ack[] = {deviceLightStateConfirmed, deviceTempConfirmed, deviceServoConfirmed};
inline String ackKey[] = {"lightState", "temp", "servo"};
inline String request[] = {serverRequestTemp, serverRequestLightState, serverRequestServo, requestAPI};
inline String requestKey[] = {"temp", "lightState", "servo", "api"};

String packToJson();

#endif