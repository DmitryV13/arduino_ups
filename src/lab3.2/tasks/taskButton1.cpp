#include "taskButton1.h"
#include "../lab32.h"

void taskButtonComponent1(void *pvParameters) 
{
  const TickType_t xFrequency = pdMS_TO_TICKS(50);
  TickType_t xLastWakeTime = xTaskGetTickCount();

  for (;;) 
  {
    if (isButtonPressed(BUTTON_PIN)) 
    {
      changeRunningMode1();

      vTaskDelay(pdMS_TO_TICKS(200));
    }
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}