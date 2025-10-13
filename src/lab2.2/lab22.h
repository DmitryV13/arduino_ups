#ifndef Lab22_H
#define Lab22_H

#include <Arduino.h>
#include "../CustomSTDIO/CustomSTDIO.h"
#include "../LCDDisplay/LCDDisplay.h"
//#include "../LED/DriverLed.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>

#define RED_LED 3
#define GREEN_LED 2

void lab22Setup();
void lab22Loop();

#endif
