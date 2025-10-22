//#include "lab1.1/lab11.h"
//#include "lab1.2/lab12.h"
//#include "lab2.1/lab21.h"
//#include "lab2.2/lab22.h"
//#include "lab3.1/lab31.h"
//#include "lab3.2/lab32.h"
#include "lab4.1/lab41.h"
//#include "lab4.2/lab42.h"

// void setup(void);
// void loop(void);

// void setup(void)
// {
//     lab41Setup();
// }

// void loop(void)
// {
//     lab41Loop();
// }

#include <LiquidCrystal.h>
#include <Arduino.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8, rw=2;
LiquidCrystal lcd1(rs, rw, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}