#ifndef Lab41_H
#define Lab41_H

#include <Arduino.h>
#include "../CustomSTDIO/CustomSTDIO.h"
#include "../LCDDisplay/LCDDisplay.h"
#include "../RelayDriver/RelayDriver.h"
#include <Arduino_FreeRTOS.h>

#define RELAY_PIN 7

void lab41Setup();
void lab41Loop();

#endif