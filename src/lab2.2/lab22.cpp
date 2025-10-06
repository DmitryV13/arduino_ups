#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Arduino_FreeRTOS.h>
#include <stdio.h>

#define BUTTON_TASK1 9
#define BUTTON_INC 10
#define BUTTON_DEC 11

#define LED_DEPENDENT 3
#define LED_BLINKING 2

LiquidCrystal lcd(13, 12, 7, 6, 5, 4);

volatile int interval = 500;
const byte additionalInterval = 50;

volatile byte redLedState = LOW;
volatile byte greenLedState = LOW;

byte previousButtonState = HIGH;
byte currentButtonState = HIGH;

boolean systemHasChanges = true;

void setup() {
  StdioSerialInit();
  lcd.begin(16, 2);
  lcd.print("System status:");

  pinMode(BUTTON_TASK1, INPUT_PULLUP);
  pinMode(BUTTON_INC, INPUT_PULLUP);
  pinMode(BUTTON_DEC, INPUT_PULLUP);

  pinMode(LED_DEPENDENT, OUTPUT);
  pinMode(LED_BLINKING, OUTPUT);

  xTaskCreate(taskLedPushButton, "LED Button", 128, NULL, 1, NULL);
  xTaskCreate(taskIncDecPushButton, "Inc/Dec Button", 128, NULL, 1, NULL);
  xTaskCreate(taskLedBlink, "LED Blink", 128, NULL, 1, NULL);
  xTaskCreate(idle, "Idle", 128, NULL, 1, NULL);

  vTaskStartScheduler();
}

void loop() {

}

void taskLedPushButton(void *pvParameters) {
  for (;;) {
    previousButtonState = currentButtonState;
    currentButtonState = digitalRead(BUTTON_TASK1);
    if (currentButtonState == LOW && currentButtonState != previousButtonState) {
      redLedState = !redLedState;
      digitalWrite(LED_DEPENDENT, redLedState);
      vTaskDelay(pdMS_TO_TICKS(100));
    }
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

void taskIncDecPushButton(void *pvParameters) {
  for (;;) {
    if(redLedState == HIGH){
      if (digitalRead(BUTTON_INC) == LOW) {
        interval += additionalInterval;
        if (interval > 1000) {
          interval = 1000;
        }
      }
      if (digitalRead(BUTTON_DEC) == LOW) {
        interval -= additionalInterval;
        if (interval < 50) {
          interval = 50;
        }
      }
    }
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

void taskLedBlink(void *pvParameters) {
  unsigned long previousMillis = 0;
  for (;;) {
    if(redLedState){
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        greenLedState = !greenLedState;
        digitalWrite(LED_BLINKING, greenLedState ? HIGH : LOW);
      }
    }
    else{
      greenLedState = LOW;
      digitalWrite(LED_BLINKING, greenLedState);
    }
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

void idle(void *pvParameters) {
  unsigned long previousMillis = 0;
  for (;;) {
    if(systemHasChanges)
    {
      char* ledStatus = (redLedState == LOW) ? "off" : "on";
      printf("Red LED is %s.\n", ledStatus);
      printf("Green LED frequency - .\n");
    }
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

static FILE *StdioStream;

static int PutChar(char ch, FILE *f)
{
    return Serial.write(ch);
}

static int GetChar(FILE *f)
{
    while (!Serial.available());
    return Serial.read();
}

void StdioSerialInit(void)
{
    Serial.begin(9600);
    StdioStream = fdevopen(PutChar, GetChar);
    stdin  = StdioStream;
    stdout = StdioStream;
}
