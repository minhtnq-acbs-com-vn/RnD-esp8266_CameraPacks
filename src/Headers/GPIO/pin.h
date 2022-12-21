#pragma once

#include <DHT.h>
#include <Servo.h>

// Init pin
const int dhtSensor = 3;
DHT dht(dhtSensor, DHT22);
Servo servo180;
Servo servo360;

const int lightSensor = 4;

const int soundSensor = 5;
const int servo180Pin = D8;
const int servo360Pin = D7;
