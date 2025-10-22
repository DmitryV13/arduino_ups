#include "lab21.h"

int task1Counter = TASK_1_OFFSET;

//to control reccurency
const byte additionalReccurency = 100;
int task2Reccurency = (TIME_SEC / 2) / SYSTEM_TICK;
int task2Counter = TASK_2_OFFSET;

int task3Counter = TASK_3_OFFSET;

unsigned long lastTick = 0;

void taskIdle();
void taskLedPushButton();
void taskLedBlink();
void taskIncDecPushButton();

byte redLedState = LOW;
byte greenLedState = LOW;

boolean systemHasChanges = true;

void lab21Setup() 
{
  StdioSerialSetup();
  buttonsSetup();

  pinMode(BUTTON_TASK1, INPUT_PULLUP);
  pinMode(BUTTON_INC, INPUT_PULLUP);
  pinMode(BUTTON_DEC, INPUT_PULLUP);

  pinMode(LED_DEPENDENT, OUTPUT);
  pinMode(LED_BLINKING, OUTPUT);

}

void lab21Loop() 
{
  //to control frequency and this adds meaning to count
  if (millis() - lastTick >= 1) 
  {

    if(--task1Counter <= 0){
      taskLedPushButton();
      task1Counter = TASK_1_RECCURENCY;
    }
  
    if(--task2Counter <= 0){
      taskLedBlink();
      task2Counter = task2Reccurency;
    }

    if(--task3Counter <= 0){
      taskIncDecPushButton();
      task3Counter = TASK_3_RECCURENCY;
    }

    taskIdle();

    lastTick = millis();
  }
}

void taskLedPushButton() 
{
    if (isButtonPressed(BUTTON_TASK1)) 
    {
      redLedState = !redLedState;
      changeLedState(LED_DEPENDENT, redLedState);

      systemHasChanges = true;
    }
}

void taskIncDecPushButton() 
{
  //edge values set blinking in visible range
    if(redLedState == LOW)
    {
      if (digitalRead(BUTTON_INC) == LOW) {
        task2Reccurency += additionalReccurency;
        if (task2Reccurency > 10000) {
          task2Reccurency = 10000;
        }
        systemHasChanges = true;
      }
      if (digitalRead(BUTTON_DEC) == LOW) {
        task2Reccurency -= additionalReccurency;
        if (task2Reccurency < 50) {
          task2Reccurency = 50;
        }
        systemHasChanges = true;
      }
    }
}

void taskLedBlink() 
{
    if(redLedState == LOW)
    {
      if (digitalRead(LED_BLINKING) == LOW) {
        ledOn(LED_BLINKING);
      }
      else{
        ledOff(LED_BLINKING);
      }
    }else{
        ledOff(LED_BLINKING);
    }
}

void taskIdle() 
{
    if(systemHasChanges)
    {
      const char* ledStatus = (redLedState == LOW) ? "off" : "on";
      int greenFreq = task2Reccurency;
      printf("============\n");
      printf("Red LED: %s | Green LED frequency: %d ms\n", ledStatus, greenFreq);

        if (digitalRead(BUTTON_INC) == LOW) {
            printf("Button INC pressed\n");
        }
        if (digitalRead(BUTTON_DEC) == LOW) {
            printf("Button DEC pressed\n");
        }
        if (digitalRead(BUTTON_TASK1) == LOW) {
            printf("Button TASK1 pressed\n");
        }

      systemHasChanges = false;
    }
    //delay(10);
}