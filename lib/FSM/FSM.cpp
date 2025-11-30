#include "FSM.h"

struct State
{
    byte curState; // LED состояние: 0=OFF,1=ON,2=BLINK
    byte inputBtn1;
    byte inputBtn2;
    byte output; // следующее состояние
};

State fsm[] = {
    {OFF, LOW, HIGH, ON},   // OFF: Btn1 -> ON, Btn2 -> OFF
    {ON, HIGH, LOW, BLINK}, // ON: Btn1 -> OFF, Btn2 -> ON
    {BLINK, LOW, HIGH, OFF} // BLINK: Btn1 -> ON, Btn2 -> OFF
};

byte fsmGetNextState(int currentState){
    return fsm[currentState].output;
}

bool checkTransition(int currentState, byte buttonState1, byte buttonState2){
	 return fsm[currentState].inputBtn1 == buttonState1 && 
       fsm[currentState].inputBtn2 == buttonState2;
}