#ifndef Lab22_H
#define Lab22_H

#include <Arduino.h>
#include "../CustomSTDIO/CustomSTDIO.h"
#include "../LCDDisplay/LCDDisplay.h"
#include "../LED/DriverLed.h"
#include "../ButtonDriver/DriverButton.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>

#define BUTTON_PIN 9
#define BUTTON_RESET 10
#define LED_TASK1_PIN 3
#define LED_TASK2_PIN 2

void lab22Setup();
void lab22Loop();

#endif
