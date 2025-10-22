#ifndef Lab21_H
#define Lab21_H

#include <Arduino.h>
#include "../CustomSTDIO/CustomSTDIO.h"
#include "../LED/DriverLed.h"
#include "../ButtonDriver/DriverButton.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define BUTTON_TASK1 9
#define BUTTON_INC 10
#define BUTTON_DEC 11

#define LED_DEPENDENT 3
#define LED_BLINKING 2

//in milliseconds
#define TIME_SEC 1000
#define SYSTEM_TICK 1

#define TASK_1_OFFSET (TIME_SEC * 1) / SYSTEM_TICK
#define TASK_1_RECCURENCY (TIME_SEC / 20) / SYSTEM_TICK

#define TASK_2_OFFSET (TIME_SEC * 2) / SYSTEM_TICK

#define TASK_3_OFFSET (TIME_SEC * 2) / SYSTEM_TICK
#define TASK_3_RECCURENCY (TIME_SEC / 20) / SYSTEM_TICK

void lab21Setup();
void lab21Loop();

#endif
