#include "lab41.h"

void processCommands1();
void controlLed1();

void lab41Setup() {
    lcdSetup();
    lcdPrint("System Ready");

    relaySetup(RELAY_PIN);
}

void lab41Loop() {
    processCommands1();
}

void controlLed1(bool turnOn) {
    setRelayState(turnOn ? HIGH : LOW);
    clearScreen();
    lcdPrint(turnOn ? "Led is ON" : "Led is OFF");
}

// Main Control Logic - Logic Layer
void processCommands1() {
    if (stdioHasData()) {
        String command = stdioGetString();
        command.trim();
        if (command.equalsIgnoreCase("on")) 
        {
            controlLed1(true);
        } else if (command.equalsIgnoreCase("off")) {
            controlLed1(false);
        } else {
            clearScreen();
            lcdPrint("Unknown cmd");
        }
    }
}