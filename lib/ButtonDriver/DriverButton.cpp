#include "DriverButton.h"

uint8_t previousButtonStates[20];
uint8_t currentButtonStates[20];

uint8_t debouncedState[20];
uint32_t lastChangeTime[20];

uint8_t debounceRead(int pin)
{
    uint8_t reading = digitalRead(pin);

    if (reading != debouncedState[pin]) {
        lastChangeTime[pin] = millis();   // ждём стабилизацию
    }

    // только если состояние не менялось >30 мс — обновляем
    if (millis() - lastChangeTime[pin] > 30) {
        debouncedState[pin] = reading;
    }

    return debouncedState[pin];
}

void buttonsSetup()
{
    for (int i = 0; i < 20; i++) {
        previousButtonStates[i] = HIGH;
        currentButtonStates[i] = HIGH;
    }
}

bool isButtonPressed(int pin)
{
    previousButtonStates[pin] = currentButtonStates[pin];
    currentButtonStates[pin] = digitalRead(pin);
  uint8_t stable = debounceRead(pin);
    if (currentButtonStates[pin] == LOW && currentButtonStates[pin] != previousButtonStates[pin] && stable == LOW) 
    {
        return true;
    }
    return false;
}

int getCurrentButtonState(int pin){
	return currentButtonStates[pin];
}

