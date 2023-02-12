#ifndef STATIC_H
#define STATIC_H

#include <Arduino.h>

#include "client.h"
#include "topic.h"
#include "packet.h"
#include "pin.h"

void publishFlag(const char *topic, const String flag);
float readTemp();
void responseTemp();
float readLightState();
void responseLightState();
void resetServo(String servoID, int degree);
void swingServo(String servoID, int degree);
void servoHandler(String request);
void publishConfirm(String type);

#endif