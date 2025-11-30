#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

#include <LiquidCrystal.h>

extern LiquidCrystal lcd;

void lcdSetup();
void clearScreen();
void lcdPrint(const char* str);
void lcdPrint(const String &str);
void lcdPrint(double v, int f);
void lcdSetCursor(int i, int j);

#endif