#include "lab22.h"

SemaphoreHandle_t xButtonSemaphore;
QueueHandle_t xDataQueue;

byte N = 0;
bool ledTask1State = LOW;

void taskButton(void *pvParameters);
void taskSync(void *pvParameters);
void taskAsync(void *pvParameters);
void taskReset(void *pvParameters);

void lab22Setup() 
{
  StdioSerialSetup();
  buttonsSetup();

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);
  pinMode(LED_TASK1_PIN, OUTPUT);
  pinMode(LED_TASK2_PIN, OUTPUT);

  xButtonSemaphore = xSemaphoreCreateBinary();
  xDataQueue = xQueueCreate(32, sizeof(byte));

  if (xButtonSemaphore != NULL && xDataQueue != NULL) 
  {
    xTaskCreate(taskButton, "Task1", 128, NULL, 1, NULL);
    xTaskCreate(taskSync,   "Task2", 256, NULL, 1, NULL);
    xTaskCreate(taskAsync,  "Task3", 256, NULL, 1, NULL);
    xTaskCreate(taskReset,  "ResetTask", 256, NULL, 1, NULL);
  }

  vTaskStartScheduler();
}

void lab22Loop() 
{

}

void taskButton(void *pvParameters) 
{
  const TickType_t xFrequency = pdMS_TO_TICKS(10);
  TickType_t xLastWakeTime = xTaskGetTickCount();

  for (;;) 
  {
    if (isButtonPressed(BUTTON_PIN)) 
    {
      ledOn(LED_TASK1_PIN);
      ledTask1State = HIGH;
      vTaskDelay(pdMS_TO_TICKS(1000));
      ledOff(LED_TASK1_PIN);
      ledTask1State = LOW;

      xSemaphoreGive(xButtonSemaphore);
    }
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

void taskSync(void *pvParameters) 
{
  for (;;) 
  {
    if (xSemaphoreTake(xButtonSemaphore, portMAX_DELAY) == pdTRUE) 
    {
      N++;
      if(N >= 255)
      {
        N = 255;
      }

      for (byte i = 1; i <= N; i++) 
      {
        xQueueSendToBack(xDataQueue, &i, 0);
        vTaskDelay(pdMS_TO_TICKS(50)); 
      }

      byte endMarker = 0;
      xQueueSendToBack(xDataQueue, &endMarker, 0);

      for (byte i = 0; i < N; i++) 
      {
        ledOn(LED_TASK2_PIN);
        vTaskDelay(pdMS_TO_TICKS(300));
        ledOff(LED_TASK2_PIN);
        vTaskDelay(pdMS_TO_TICKS(500));
      }
    }
  }
}

void taskAsync(void *pvParameters) 
{
  byte receivedByte = 0;

  for (;;) 
  {
    if (xQueueReceive(xDataQueue, &receivedByte, pdMS_TO_TICKS(200)) == pdTRUE) 
    {
      if (receivedByte == 0) 
      {
        printf("\n");
      } else {
        printf("%d ", receivedByte);
      }
    } else {
      vTaskDelay(pdMS_TO_TICKS(200));
    }
  }
}

void taskReset(void *pvParameters) 
{
  for (;;) 
  {
    if (digitalRead(BUTTON_RESET) == LOW) 
    {
      N = 0;
      vTaskDelay(pdMS_TO_TICKS(300));
    }

    vTaskDelay(pdMS_TO_TICKS(20));
  }
}