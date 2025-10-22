#ifndef Lab31_H
#define Lab31_H

#include <Arduino.h>
#include "../CustomSTDIO/CustomSTDIO.h"
#include "../LCDDisplay/LCDDisplay.h"
#include "../LED/DriverLed.h"
#include "../ButtonDriver/DriverButton.h"
#include "tasks/taskButton.h"
#include "tasks/taskGas.h"
#include "tasks/taskUltrasonic.h"
#include <Arduino_FreeRTOS.h>

#define BUTTON_PIN 13
#define LED_RED_PIN 3
#define LED_GREEN_PIN 2

#define PIN_TRIG 10
#define PIN_ECHO 8
#define MQ2_PIN A0

extern int gasSensorAnalogValue;
extern int gasSensorVoltage;

extern int ultrasonicSensorDuration;
extern int ultrasonicSensorDistance;

extern byte runningMode;

void lab31Setup();
void lab31Loop();
void changeRunningMode();

#endif