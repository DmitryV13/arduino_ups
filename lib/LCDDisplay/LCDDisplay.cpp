#include "LCDDisplay.h"

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

void lcdInit() {
  lcd.begin(16, 2);
  lcd.print("Enter Code:");
}
