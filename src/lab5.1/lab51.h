#ifndef Lab51_H
#define Lab51_H

#include <Arduino.h>
#include "../CustomSTDIO/CustomSTDIO.h"
#include "../LCDDisplay/LCDDisplay.h"
#include "../MotorDriver/MotorDriver.h"
#include <Arduino_FreeRTOS.h>

// Enable pin for PWM speed control
#define  MOTOR_ENABLE_PIN 6
// Input 1 for direction
#define  MOTOR_PIN1 5
// Input 2 for direction
#define  MOTOR_PIN2 4

void lab51Setup();
void lab51Loop();

#endif