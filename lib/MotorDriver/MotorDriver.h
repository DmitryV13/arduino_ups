#ifndef DRIVER_MOTOR_H
#define DRIVER_MOTOR_H

#include <Arduino.h>

void motorSetup(int mep, int mp1, int mp2);
void setSpeed(int speed);
int getSpeed();

#endif