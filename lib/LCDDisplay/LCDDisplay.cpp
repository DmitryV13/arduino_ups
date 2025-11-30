#include "LCDDisplay.h"

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void lcdSetup() 
{
  lcd.begin(16, 2);
}

void clearScreen()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}

void lcdPrint(const char* str)
{
  lcd.print(str);
}

void lcdPrint(const String &str)
{
  lcd.print(str);
}

void lcdPrint(double v, int f)
{
  lcd.print(v, f);
}

void lcdSetCursor(int i, int j)
{
  lcd.setCursor(i, j);
}