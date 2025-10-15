#include "taskButton.h"
#include "../lab31.h"

void taskButtonComponent(void *pvParameters) 
{
  const TickType_t xFrequency = pdMS_TO_TICKS(50);
  TickType_t xLastWakeTime = xTaskGetTickCount();

  for (;;) 
  {
    if (isButtonPressed(BUTTON_PIN)) 
    {
      changeRunningMode();

      vTaskDelay(pdMS_TO_TICKS(200));
    }
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}