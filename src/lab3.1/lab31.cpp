#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>
#include <stdio.h>

#define BUTTON_PIN 13
#define LED_RED_PIN 3
#define LED_GREEN_PIN 2

#define PIN_TRIG 12
#define PIN_ECHO 11
#define MQ2_PIN A0

int gasSensorAnalogValue = 0;
int gasSensorVoltage = 0;

long ultrasonicSensorDuration = 0;
int ultrasonicSensorDistance = 0;

SemaphoreHandle_t xButtonSemaphore;
QueueHandle_t xDataQueue;

byte prevButtonState = HIGH;
byte currentButtonState = HIGH;
bool ledTask1State = LOW;
byte runningMode = 0;

void taskButton(void *pvParameters);
void taskUltrasonicSensor(void *pvParameters);
void taskGasSensor(void *pvParameters);
void taskReport(void *pvParameters);

void changeRunningMode();

static FILE *StdioStream;

static int PutChar(char ch, FILE *f) 
{ 
  return Serial.write(ch); 
}

static int GetChar(FILE *f) 
{ 
  while (!Serial.available()); return Serial.read(); 
}

void StdioSerialInit(void) 
{
  Serial.begin(9600);
  StdioStream = fdevopen(PutChar, GetChar);
  stdin  = StdioStream;
  stdout = StdioStream;
}

void setup() 
{
  StdioSerialInit();

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  pinMode(MQ2_PIN, INPUT);

  xButtonSemaphore = xSemaphoreCreateBinary();
  xDataQueue = xQueueCreate(32, sizeof(byte));

  if (xButtonSemaphore != NULL && xDataQueue != NULL) 
  {
    xTaskCreate(taskButton, "TaskButton", 128, NULL, 1, NULL);
    xTaskCreate(taskUltrasonicSensor,   "TaskUltrasonic", 256, NULL, 1, NULL);
    xTaskCreate(taskGasSensor,  "TaskGas", 256, NULL, 1, NULL);
    xTaskCreate(taskReport,  "TaskReport", 256, NULL, 1, NULL);
  }

  vTaskStartScheduler();
}

void loop() 
{

}

void taskButton(void *pvParameters) 
{
  const TickType_t xFrequency = pdMS_TO_TICKS(50);
  TickType_t xLastWakeTime = xTaskGetTickCount();

  for (;;) 
  {
    prevButtonState = currentButtonState;
    currentButtonState = digitalRead(BUTTON_PIN);
    if (currentButtonState == LOW && currentButtonState != prevButtonState) 
    {
      changeRunningMode();

      xSemaphoreGive(xButtonSemaphore);
      vTaskDelay(pdMS_TO_TICKS(200));
    }
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

void taskUltrasonicSensor(void *pvParameters) 
{
  const TickType_t xFrequency = pdMS_TO_TICKS(1000);
  TickType_t xLastWakeTime = xTaskGetTickCount();

  for (;;)
  {
    if(runningMode == 1 || runningMode == 3)
    {
      digitalWrite(PIN_TRIG, LOW);
      vTaskDelay(pdMS_TO_TICKS(2));
      digitalWrite(PIN_TRIG, HIGH);
      vTaskDelay(pdMS_TO_TICKS(1));
      digitalWrite(PIN_TRIG, LOW);

      // mks
      ultrasonicSensorDuration = pulseIn(PIN_ECHO, HIGH);
      //0-400 cm
      ultrasonicSensorDistance = (int)(ultrasonicSensorDuration * 0.034 / 2);
    }

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

void taskGasSensor(void *pvParameters) 
{
  const TickType_t xFrequency = pdMS_TO_TICKS(500);
  TickType_t xLastWakeTime = xTaskGetTickCount();


  for (;;)
  {
    if(runningMode == 2 || runningMode == 3)
    {
      // 0 - 1023
      gasSensorAnalogValue = analogRead(MQ2_PIN);
      //0 - 5000 mV
      gasSensorVoltage = gasSensorAnalogValue * (5.0 / 1023.0) * 1000;
    }

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

void taskReport(void *pvParameters) 
{
  const TickType_t xFrequency = pdMS_TO_TICKS(500);
  TickType_t xLastWakeTime = xTaskGetTickCount();

  for (;;)
  {
    printf("=======================\n");
    printf("Report:\n");
    printf("Gas sensor analog value: %d \n", gasSensorAnalogValue);
    printf("Gas sensor voltage: %d mV\n", gasSensorVoltage);

    printf("Duration: %d mks\n", ultrasonicSensorDuration);
    printf("Distance: %d cm\n", ultrasonicSensorDistance);

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

void changeRunningMode(){
  runningMode++;
  if(runningMode >= 4){
    runningMode = 0;
  }
  switch(runningMode){
    case 0:
    {
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_GREEN_PIN, LOW);
      gasSensorAnalogValue = 0;
      gasSensorVoltage = 0;
      ultrasonicSensorDuration = 0;
      ultrasonicSensorDistance = 0;
      break;
    }
    case 1:
    {
      digitalWrite(LED_RED_PIN, HIGH);
      digitalWrite(LED_GREEN_PIN, LOW);
      gasSensorAnalogValue = 0;
      gasSensorVoltage = 0;
      break;
    }
    case 2:
    {
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_GREEN_PIN, HIGH);
      ultrasonicSensorDuration = 0;
      ultrasonicSensorDistance = 0;
      break;
    }
    case 3:
    {
      digitalWrite(LED_RED_PIN, HIGH);
      digitalWrite(LED_GREEN_PIN, HIGH);
      break;
    }
  }
}