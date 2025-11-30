#include "lab61.h"

unsigned long lastTick1 = 0;
bool systemHasChanges2 = true;

byte redLedState1 = LOW;

byte currentState = OFF;

void stateLedOff();
void stateLedOn();
void stateLedBlink();
void printState();

ActionFunc actions[] = {stateLedOff, stateLedOn, stateLedBlink};

int task3Counter1 = TASK_3_OFFSET;

void lab61Setup()
{
    buttonsSetup();
    ledSetup(RED_LED_PIN);
    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);

    ledOff(RED_LED_PIN);
    StdioSerialSetup();
}

void lab61Loop()
{
    // to control frequency
    if (millis() - lastTick1 >= 1)
    {
        if (isButtonPressed(BUTTON1_PIN))
        {
            if (checkTransition(currentState, getCurrentButtonState(BUTTON1_PIN), getCurrentButtonState(BUTTON2_PIN)))
            {
                systemHasChanges2 = true;
                currentState = fsmGetNextState(currentState);
            }

            printf("Button1 pressed");
        }

        if (isButtonPressed(BUTTON2_PIN))
        {
            if (checkTransition(currentState, getCurrentButtonState(BUTTON1_PIN), getCurrentButtonState(BUTTON2_PIN)))
            {
                systemHasChanges2 = true;
                currentState = fsmGetNextState(currentState);
            }
            printf("Button2 pressed");
        }

        // to control frequency of blinking
        if (--task3Counter1 <= 0)
        {
            actions[currentState]();
            task3Counter1 = TASK_3_RECCURENCY;
        }

        printState();

        lastTick1 = millis();
    }
}

void stateLedBlink()
{
    if (redLedState1 == LOW)
    {
        if (digitalRead(RED_LED_PIN) == LOW)
        {
            ledOn(RED_LED_PIN);
        }
        else
        {
            ledOff(RED_LED_PIN);
        }
    }
    else
    {
        ledOff(RED_LED_PIN);
    }
}

void stateLedOff()
{
    digitalWrite(RED_LED_PIN, LOW);
}

void stateLedOn()
{
    digitalWrite(RED_LED_PIN, HIGH);
}

void printState()
{
    if (systemHasChanges2)
    {
        if (currentState == 0)
        {
            printf("Current state: LED OFF");
        }
        else if (currentState == 1)
        {
            printf("Current state: LED ON");
        }
        else if (currentState == 2)
        {
            printf("Current state: LED IS BLINKING");
        }

        systemHasChanges2 = false;
    }
}
