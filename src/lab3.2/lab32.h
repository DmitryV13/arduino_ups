#ifndef Lab32_H
#define Lab32_H

#include <Arduino.h>
#include "../CustomSTDIO/CustomSTDIO.h"
#include "../LCDDisplay/LCDDisplay.h"
#include "../LED/DriverLed.h"
#include "../ButtonDriver/DriverButton.h"
#include "tasks/taskButton1.h"
#include "tasks/taskGas1.h"
#include "tasks/taskUltrasonic1.h"
#include <Arduino_FreeRTOS.h>

#define BUTTON_PIN 13
#define LED_RED_PIN 3
#define LED_GREEN_PIN 2

#define PIN_TRIG 12
#define PIN_ECHO 11
#define MQ2_PIN A0

#define BUFFER_SIZE 5
#define INJECT_TEST_NOISE 1 

extern int gasSensorAnalogValue1;
extern int gasSensorVoltage1;

extern int ultrasonicSensorDuration1;
extern int ultrasonicSensorDistance1;

extern byte runningMode1;

extern float gasBuffer[BUFFER_SIZE];
extern float distanceBuffer[BUFFER_SIZE];
extern int bufferIndexGas;
extern int bufferIndexDist;
extern bool bufferFilledGas;
extern bool bufferFilledDist;

extern float gasMedium;
extern float gasWeighted;
extern float distMedium;
extern float distWeighted;

void lab32Setup();
void lab32Loop();
void changeRunningMode1();
void updateFilters(float *buffer, int size, float &saltOut, float &weightedOut, bool filled, int currentIndex);

#endif