#ifndef Lab61_H
#define Lab61_H

#include <Arduino.h>
#include "../CustomSTDIO/CustomSTDIO.h"
#include "../FSM/FSM.h"
#include "../ButtonDriver/DriverButton.h"
#include "../LED/DriverLed.h"

#define RED_LED_PIN 8
#define BUTTON1_PIN 9
#define BUTTON2_PIN 10

//in milliseconds
#define TIME_SEC 1000
#define SYSTEM_TICK 1

#define TASK_3_OFFSET (TIME_SEC * 2) / SYSTEM_TICK
#define TASK_3_RECCURENCY (TIME_SEC / 50) / SYSTEM_TICK

void lab61Setup();
void lab61Loop();

#endif