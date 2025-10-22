#ifndef DRIVER_RELAY_H
#define DRIVER_RELAY_H

#include <Arduino.h>

void relaySetup(int rp);
void setRelayState(int state);
void relayOpen();
void relayClose();

#endif