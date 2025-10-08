// #include <Arduino.h>
// #include <LiquidCrystal.h>
// #include <stdio.h>

// #define BUTTON_TASK1 9
// #define BUTTON_INC 10
// #define BUTTON_DEC 11

// #define LED_DEPENDENT 3
// #define LED_BLINKING 2


// #define TIME_SEC 1000
// #define SYSTEM_TICK 1

// #define TASK_1_OFFSET (TIME_SEC * 1) / SYSTEM_TICK
// #define TASK_1_RECCURENCY (TIME_SEC / 20) / SYSTEM_TICK
// int task1Counter = TASK_1_OFFSET;

// #define TASK_2_OFFSET (TIME_SEC * 2) / SYSTEM_TICK
// int task2Reccurency = (TIME_SEC / 2) / SYSTEM_TICK;
// const byte additionalReccurency = 100;
// int task2Counter = TASK_2_OFFSET;

// #define TASK_3_OFFSET (TIME_SEC * 2) / SYSTEM_TICK
// #define TASK_3_RECCURENCY (TIME_SEC / 20) / SYSTEM_TICK
// int task3Counter = TASK_3_OFFSET;

// unsigned long lastTick = 0;


// LiquidCrystal lcd(13, 12, 7, 6, 5, 4);



// byte redLedState = LOW;
// byte greenLedState = LOW;

// byte previousButtonState = HIGH;
// byte currentButtonState = HIGH;

// boolean systemHasChanges = true;

// void setup() {
//   StdioSerialInit();
//   lcd.begin(16, 2);

//   pinMode(BUTTON_TASK1, INPUT_PULLUP);
//   pinMode(BUTTON_INC, INPUT_PULLUP);
//   pinMode(BUTTON_DEC, INPUT_PULLUP);

//   pinMode(LED_DEPENDENT, OUTPUT);
//   pinMode(LED_BLINKING, OUTPUT);

// }

// void loop() {
//   if (millis() - lastTick >= 1) {

//     if(--task1Counter <= 0){
//       taskLedPushButton();
//       task1Counter = TASK_1_RECCURENCY;
//     }
  
//     if(--task2Counter <= 0){
//       taskLedBlink();
//       task2Counter = task2Reccurency;
//     }

//     if(--task3Counter <= 0){
//       taskIncDecPushButton();
//       task3Counter = TASK_3_RECCURENCY;
//     }

//     taskIdle();

//     lastTick = millis();
//   }
// }

// void taskLedPushButton() {
//     previousButtonState = currentButtonState;
//     currentButtonState = digitalRead(BUTTON_TASK1);
//     if (currentButtonState == LOW && currentButtonState != previousButtonState) {
//       redLedState = !redLedState;
//       digitalWrite(LED_DEPENDENT, redLedState);

//       systemHasChanges = true;
//     }
// }

// void taskIncDecPushButton() {
//     if(redLedState == HIGH){
//       if (digitalRead(BUTTON_INC) == LOW) {
//         task2Reccurency += additionalReccurency;
//         if (task2Reccurency > 10000) {
//           task2Reccurency = 10000;
//         }
//         lcdPrint("Decrease ferq.");
//         systemHasChanges = true;
//       }
//       if (digitalRead(BUTTON_DEC) == LOW) {
//         task2Reccurency -= additionalReccurency;
//         if (task2Reccurency < 50) {
//           task2Reccurency = 50;
//         }
//         lcdPrint("Increase ferq.");
//         systemHasChanges = true;
//       }
//     }
// }

// void taskLedBlink() {
//   if(redLedState == HIGH){
//       if (digitalRead(LED_BLINKING) == LOW) {
//         digitalWrite(LED_BLINKING, HIGH);
//       }
//       else{
//         digitalWrite(LED_BLINKING, LOW);
//       }
//     }
// }

// void taskIdle() {
//     if(systemHasChanges)
//     {
//       char* ledStatus = (redLedState == LOW) ? "off" : "on";
//       int greenFreq = task2Reccurency;
//       printf("============\n");
//       printf("Red LED: %s | Green LED frequency: %d ms\n", ledStatus, greenFreq);

//         if (digitalRead(BUTTON_INC) == LOW) {
//             printf("Button INC pressed\n");
//         }
//         if (digitalRead(BUTTON_DEC) == LOW) {
//             printf("Button DEC pressed\n");
//         }
//         if (digitalRead(BUTTON_TASK1) == LOW) {
//             printf("Button TASK1 pressed\n");
//         }

//       systemHasChanges = false;
//     }
//     delay(10);
// }

// static FILE *StdioStream;

// static int PutChar(char ch, FILE *f)
// {
//     return Serial.write(ch);
// }

// static int GetChar(FILE *f)
// {
//     while (!Serial.available());
//     return Serial.read();
// }

// void StdioSerialInit(void)
// {
//     Serial.begin(9600);
//     StdioStream = fdevopen(PutChar, GetChar);
//     stdin  = StdioStream;
//     stdout = StdioStream;
// }

// void lcdPrint(char* str){
//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print(str); 
// }