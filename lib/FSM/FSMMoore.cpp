#include "FSMMoore.h"

// FSM
State1 fsm1[] = {
    {GREEN, RED, STATIC, 2000 / portTICK_PERIOD_MS, 1},    // A
    {GREEN, RED, BLINK_S, 2000 / portTICK_PERIOD_MS, 2},   // B
    {YELLOW, RED, BLINK_S, 4000 / portTICK_PERIOD_MS, 3},  // C
    {RED, GREEN, STATIC, 5000 / portTICK_PERIOD_MS, 4},    // D
    {YELLOW, GREEN, BLINK_S, 3000 / portTICK_PERIOD_MS, 0} // F
};