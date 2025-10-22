#ifndef Lab42_H
#define Lab42_H

#include <Arduino.h>
#include "../CustomSTDIO/CustomSTDIO.h"
#include "../LCDDisplay/LCDDisplay.h"
#include "../MotorDriver/MotorDriver.h"
#include "../RelayDriver/RelayDriver.h"
#include <Arduino_FreeRTOS.h>

#define RELAY_PIN 7

// Enable pin for PWM speed control
#define  MOTOR_ENABLE_PIN 6
// Input 1 for direction
#define  MOTOR_PIN1 5
// Input 2 for direction
#define  MOTOR_PIN2 4

void lab42Setup();
void lab42Loop();

#endif