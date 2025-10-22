#ifndef Lab12_H
#define Lab12_H

#include <Arduino.h>
#include "CustomSTDIO.h"
#include "../CustomKeypad/CustomKeypad.h"
#include "../LCDDisplay/LCDDisplay.h"
#include "../LED/DriverLed.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define RED_LED 3
#define GREEN_LED 2

void lab12Setup();
void lab12Loop();

#endif
