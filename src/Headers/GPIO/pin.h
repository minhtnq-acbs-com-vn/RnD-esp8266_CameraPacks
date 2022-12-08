#pragma once

#include <DHT.h>
#include <Servo.h>

// Init pin
const int dhtSensor = 3;
DHT dht(dhtSensor, DHT22);
Servo myServo;

const int lightSensor = 4;

const int soundSensor = 5;
const int servoPin = 6;
