#ifndef FSM
#define FSM

#include <Arduino.h>

#define OFF 0
#define ON 1
#define BLINK 2

struct State;

extern State fsm[];

typedef void (*ActionFunc)(); // тип для указателя на функцию void()

byte fsmGetNextState(int currentState);
bool checkTransition(int currentState, byte buttonState1, byte buttonState2);

#endif