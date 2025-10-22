#include "lab12.h"

const char correctCode[] = "1234";
char inputCode[5];
int codeIndex = 0;

void lab12Setup() {
  StdioSerialSetup();
  lcdSetup();

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  ledOff(RED_LED);
  ledOff(GREEN_LED);
}

void showMessage(char* msg) {
    clearScreen();
    lcdPrint(msg);
}

void resetInput() {
    codeIndex = 0;
    clearScreen();
    lcdPrint("Enter Code:");
}

void setAccessLED(bool granted) {
  if(granted) {
    ledOn(GREEN_LED);
    ledOff(RED_LED);
  } else {
    ledOff(GREEN_LED);
    ledOn(RED_LED);
  }
}

void lab12Loop() {
    char key = keypad.getKey();
    if (!key) return;

    printf("[KEYPAD] Pressed key: %c\n", key);

    if (isdigit(key) && codeIndex < 4) {
        inputCode[codeIndex++] = key;
        lcdSetCursor(codeIndex - 1, 1);
        lcdPrint("*");
    }

    if (key == '#') {
        inputCode[codeIndex] = '\0';

        if (strcmp(inputCode, correctCode) == 0) {
            showMessage("Access Granted");
            printf("[SYSTEM] Correct code entered\n");
            setAccessLED(true);
        } else {
            showMessage("Access Denied");
            printf("[SYSTEM] Wrong code: %s\n", inputCode);
            setAccessLED(false);
        }

        delay(2000);
        resetInput();
    }

    if (key == '*') {
        printf("[SYSTEM] Code cleared\n");
        resetInput();
    }
}