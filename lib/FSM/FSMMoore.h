#ifndef FSM_MOORE
#define FSM_MOORE

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

// FSM состояния
enum SState
{
    GREEN,
    YELLOW,
    RED,
    EMPTY
};

enum BlinkState
{
    STATIC,
    BLINK_S
};

// Структура состояния FSM
struct State1
{
    SState car;
    SState human;
    BlinkState blink;
    TickType_t delayTime; // задержка в мс
    int nextState;
};

extern State1 fsm1[];

#endif