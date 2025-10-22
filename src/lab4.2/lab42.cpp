#include "lab42.h"

void processCommands();
void controlLed();

void lab42Setup() {
    lcdSetup();
    lcdPrint("System Ready");

    motorSetup(MOTOR_ENABLE_PIN, MOTOR_PIN1, MOTOR_PIN2);
    relaySetup(RELAY_PIN);
}

void lab42Loop() {
    processCommands();
}

void controlLed(bool turnOn) {
    setRelayState(turnOn ? HIGH : LOW);
    clearScreen();
    lcdPrint(turnOn ? "Led is ON" : "Led is OFF");
}

void controlMotor(int speed) {
    setSpeed(speed);
    if (speed == 0) {
        lcdSetCursor(0, 1);
        lcdPrint("Motor is OFF     ");
    } else {
        lcdSetCursor(0, 1);
        lcdPrint("Motor Speed:" + String(speed));
    }
}

// Main Control Logic - Logic Layer
void processCommands() {
    if (stdioHasData()) {
        String command = stdioGetString();
        command.trim();
        if (command.equalsIgnoreCase("on")) {
            controlLed(true);
        } else if (command.equalsIgnoreCase("off")) {
            controlLed(false);
        } else if (command.startsWith("speed ")) {
            // Extract speed from command, expected format "MOTOR 100" or "MOTOR -90"
            int speed = command.substring(6).toInt(); // Convert the numerical part
            controlMotor(map(speed, -100, 100, -255, 255)); // Map from -100-100 to -255-255 PWM range
        }
    }
}