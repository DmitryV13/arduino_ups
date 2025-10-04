#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <Arduino.h>

#define RED_LED 3
#define GREEN_LED 2

void ledsInit();
void setAccessLED(bool granted);

#endif
