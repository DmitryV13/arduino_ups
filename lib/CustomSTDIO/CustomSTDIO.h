#ifndef CustomSTDIO_H
#define CustomSTDIO_H

#include <Arduino.h>
#include <stdio.h>

void StdioSerialSetup(void);
void printFloat(const char* label, float value, const char* suffix);
bool stdioHasData();
String stdioGetString();

#endif