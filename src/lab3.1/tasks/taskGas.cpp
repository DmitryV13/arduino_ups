#include "taskGas.h"
#include "../lab31.h"

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