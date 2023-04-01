#ifndef PIN_H
#define PIN_H

#include "DHT.h"
#include <Servo.h>

// Init pin
inline int dhtSensor = D1;
inline DHT dht(dhtSensor, DHT22);
inline Servo servo180;
inline Servo servo360;

inline int lightSensor = 2;

inline int servo360Pin = D7;
inline int servo180Pin = D8;

inline int pin[] = {dhtSensor, lightSensor, servo360Pin, servo180Pin};
inline String pinKey[] = {"dht", "lightState", "servo360", "servo180"};

#endif