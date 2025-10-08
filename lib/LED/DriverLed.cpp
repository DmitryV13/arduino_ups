#include "DriverLed.h"


void ledSetup(int pin)
{
}

void ledOn(int pin)
{
    digitalWrite(pin, HIGH);
}

void ledOff(int pin)
{
    digitalWrite(pin, LOW);
}