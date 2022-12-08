#pragma once
#include <Arduino.h>

// Setup string
const String serverRequestTemp = "requestTemp";
const String serverRequestLightState = "requestLightState";
const String serverRequestSoundState = "requestSoundState";
const String serverRequestServo = "requestServo";

const String lightID = "Light: ";
const String tempID = "Temp: ";
const String soundID = "Sound: ";

const String typeOfConfirmation_LightState = "light_state";
const String typeOfConfirmation_Temp = "temp";
const String typeOfConfirmation_SoundState = "sound_state";
const String typeOfConfirmation_Servo = "servo";

const String deviceLightStateConfirmed = "deviceLightStateConfirmed";
const String deviceTempConfirmed = "deviceTempConfirmed";
const String deviceSoundStateConfirmed = "deviceSoundStateConfirmed";
const String deviceServoConfirmed = "deviceServoConfirmed";

const int defaultDegree = 0;
const int degree = 180;