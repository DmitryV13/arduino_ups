#include "MotorDriver.h"

int motorEnablePin = 0;
int motorPin1 = 0;
int motorPin2 = 0;

void motorSetup(int mep, int mp1, int mp2){
    motorEnablePin = mep;
    motorPin1 = mp1;
    motorPin2 = mp2;

    // Motor driver setup
    pinMode(motorEnablePin, OUTPUT);
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    digitalWrite(motorEnablePin, LOW);  // Start with the motor off
}

void setSpeed(int speed){
    if (speed == 0) {
        digitalWrite(motorEnablePin, LOW); // Turn motor off
    } else {
        int dir = speed > 0 ? HIGH : LOW;
        digitalWrite(motorPin1, !dir);
        digitalWrite(motorPin2, dir);
        analogWrite(motorEnablePin, abs(speed)); // Set speed
    }
}