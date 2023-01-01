#ifndef PACKET_H
#define PACKET_H

#include <Arduino.h>

// Setup string
inline String serverRequestTemp = "requestTemp";
inline String serverRequestLightState = "requestLightState";
inline String serverRequestSoundState = "requestSoundState";
inline String serverRequestServo = "requestServo";

inline String lightID = "Light: ";
inline String tempID = "Temp: ";
inline String soundID = "Sound: ";

inline String typeOfConfirmation_LightState = "light_state";
inline String typeOfConfirmation_Temp = "temp";
inline String typeOfConfirmation_SoundState = "sound_state";
inline String typeOfConfirmation_Servo = "servo";

inline String deviceLightStateConfirmed = "deviceLightStateConfirmed";
inline String deviceTempConfirmed = "deviceTempConfirmed";
inline String deviceSoundStateConfirmed = "deviceSoundStateConfirmed";
inline String deviceServoConfirmed = "deviceServoConfirmed";

inline int defaultDegree = 0;
inline int degree = 180;

#endif