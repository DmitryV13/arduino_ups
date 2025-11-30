#ifndef Lab62_H
#define Lab62_H

#include <Arduino.h>
#include "../CustomSTDIO/CustomSTDIO.h"
#include "../FSM/FSMMoore.h"
#include "../ButtonDriver/DriverButton.h"
#include "../LED/DriverLed.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// Пины машинного светофора
#define CAR_RED_PIN 7
#define CAR_YELLOW_PIN 6
#define CAR_GREEN_PIN 5

// Пины пешеходного светофора
#define PED_RED_PIN 10
#define PED_GREEN_PIN 8

// Пин кнопки пешехода
#define BUTTON_PED_PIN 11

void lab62Setup();
void lab62Loop();

#endif