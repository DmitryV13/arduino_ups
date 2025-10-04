#include "lab12.h"

const char correctCode[] = "1234";
char inputCode[5];
int codeIndex = 0;

void lab12_setup() {
  StdioSerialInit();
  lcdInit();
  ledsInit();
}

void lab12_loop() {
  char key = keypad.getKey();

  if (key) {
    printf("[KEYPAD] Pressed key: %c\n", key);

    if (isdigit(key)) {
      if (codeIndex < 4) {
        inputCode[codeIndex++] = key;
        lcd.setCursor(codeIndex - 1, 1);
        lcd.print("*");
      }
    }

    if (key == '#') {
      inputCode[codeIndex] = '\0';

      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);

      if (strcmp(inputCode, correctCode) == 0) {
        lcd.print("Access Granted");
        printf("[SYSTEM] Correct code entered\n");
        setAccessLED(true);
      } else {
        lcd.print("Access Denied ");
        printf("[SYSTEM] Wrong code entered: %s\n", inputCode);
        setAccessLED(false);
      }

      codeIndex = 0;
      delay(2000);
      lcd.clear();
      lcd.print("Enter Code:");
    }

    if (key == '*') {
      codeIndex = 0;
      lcd.setCursor(0, 1);
      lcd.print("                ");
      printf("[SYSTEM] Code cleared\n");
    }
  }
}


