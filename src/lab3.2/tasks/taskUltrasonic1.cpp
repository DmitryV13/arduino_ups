#include "taskUltrasonic1.h"
#include "../lab32.h"

void taskUltrasonicSensor1(void *pvParameters) 
{
  const TickType_t xFrequency = pdMS_TO_TICKS(1000);
  TickType_t xLastWakeTime = xTaskGetTickCount();

  for (;;)
  {
    if(runningMode1 == 1 || runningMode1 == 3)
    {
      digitalWrite(PIN_TRIG, LOW);
      vTaskDelay(pdMS_TO_TICKS(2));
      digitalWrite(PIN_TRIG, HIGH);
      vTaskDelay(pdMS_TO_TICKS(1));
      digitalWrite(PIN_TRIG, LOW);

      // mks
      ultrasonicSensorDuration1 = pulseIn(PIN_ECHO, HIGH);
      //0-400 cm
      float distance = ultrasonicSensorDuration1 * 0.034 / 2;

      if(INJECT_TEST_NOISE == 1)
      {
            float jitter = random(-20, 21) / 10.0;
            if (random(0, 10) == 0) {
              jitter += 15.0;
            }
            distance += jitter;
      }

      ultrasonicSensorDistance1 = (int)distance;

      distanceBuffer[bufferIndexDist] = distance;
      bufferIndexDist++;
      if (bufferIndexDist >= BUFFER_SIZE) 
      {
        bufferIndexDist = 0;
        bufferFilledDist = true;
      }

      updateFilters(distanceBuffer, BUFFER_SIZE, distMedium, distWeighted, bufferFilledDist, bufferIndexDist);
    }

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}