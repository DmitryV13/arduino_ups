#ifndef Lab51_H
#define Lab51_H

#include <Arduino.h>
#include "../CustomSTDIO/CustomSTDIO.h"
#include "../LCDDisplay/LCDDisplay.h"
#include "../RelayDriver/RelayDriver.h"

#define  RELAY_PIN1 7
#define  TMP_PIN A0

void lab51Setup();
void lab51Loop();

#endif