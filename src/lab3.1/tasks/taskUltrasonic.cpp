#include "taskUltrasonic.h"
#include "../lab31.h"

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