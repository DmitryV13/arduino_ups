#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

#include <LiquidCrystal.h>

extern LiquidCrystal lcd;

void lcdSetup();
void clearScreen();
void lcdPrint(char* str);
void lcdSetCursor(int i, int j);

#endif