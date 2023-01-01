#ifndef PIN_H
#define PIN_H

#include <DHT.h>
#include <Servo.h>

// Init pin
inline int dhtSensor = 3;
inline DHT dht(dhtSensor, DHT22);
inline Servo servo180;
inline Servo servo360;

inline int lightSensor = 4;

inline int soundSensor = 5;
inline int servo180Pin = D8;
inline int servo360Pin = D7;

#endif