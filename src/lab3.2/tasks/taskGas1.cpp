#include "taskGas1.h"
#include "../lab32.h"

void taskGasSensor1(void *pvParameters) 
{
  const TickType_t xFrequency = pdMS_TO_TICKS(500);
  TickType_t xLastWakeTime = xTaskGetTickCount();

  for (;;)
  {
    if(runningMode1 == 2 || runningMode1 == 3)
    {
      float value = analogRead(MQ2_PIN);

      if(INJECT_TEST_NOISE == 1)
      {
        float jitter = random(-30, 31);
        if (random(0, 10) == 0) {
          jitter += 200;
        }
        value += jitter;
        if (value < 0) {
          value = 0;
        }
        if (value > 1023) {
          value = 1023;
        }
      }

      gasSensorAnalogValue1 = (int)value;
      gasSensorVoltage1 = gasSensorAnalogValue1 * (5.0 / 1023.0) * 1000;

      gasBuffer[bufferIndexGas] = value;
      bufferIndexGas++;
      if (bufferIndexGas >= BUFFER_SIZE) {
        bufferIndexGas = 0;
        bufferFilledGas = true;
      }

      updateFilters(gasBuffer, BUFFER_SIZE, gasMedium, gasWeighted, bufferFilledGas, bufferIndexGas);
    }

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}