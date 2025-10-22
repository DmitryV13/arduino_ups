#include "RelayDriver.h"

int relayPin = 0;

void relaySetup(int rp, int mp1, int mp2){
    relayPin = rp;
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW);
}

void setRelayState(int state){
    digitalWrite(relayPin, state);
}

void relayOpen(){
    digitalWrite(relayPin, HIGH);
}

void relayClose(){
    digitalWrite(relayPin, LOW);
}