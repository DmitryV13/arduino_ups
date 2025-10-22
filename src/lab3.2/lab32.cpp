#include "lab32.h"

int gasSensorAnalogValue1 = 0;
int gasSensorVoltage1 = 0;

int ultrasonicSensorDuration1 = 0;
int ultrasonicSensorDistance1 = 0;

float gasBuffer[BUFFER_SIZE];
float distanceBuffer[BUFFER_SIZE];
int bufferIndexGas = 0;
int bufferIndexDist = 0;
bool bufferFilledGas = false;
bool bufferFilledDist = false;

// for filtering
float gasMedium = 0;
float gasWeighted = 0;
float distMedium = 0;
float distWeighted = 0;

byte runningMode1 = 0;

float mediumFilter(float *arr, int n) 
{
  float temp[n];
  memcpy(temp, arr, n * sizeof(float));
  // sorting
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      if (temp[j] < temp[i]) {
        float t = temp[i];
        temp[i] = temp[j];
        temp[j] = t;
      }
    }
  }
  float sum = 0;
  for (int i = 1; i < n - 1; i++) 
  {
    sum += temp[i];
  }
  return sum / (n - 2);
}

float weightedAverageFilter(float *arr, int n) 
{
  int weights[] = {1, 2, 3, 2, 1};
  float sum = 0;
  int sumW = 0;
  for (int i = 0; i < n; i++) 
  {
    sum += arr[i] * weights[i];
    sumW += weights[i];
  }
  return sum / sumW;
}

void updateFilters(float *buffer, int size, float &saltOut, float &weightedOut, bool filled, int currentIndex) 
{
  int valid = filled ? size : currentIndex;
  if (valid > 2) {
    saltOut = mediumFilter(buffer, valid);
    weightedOut = weightedAverageFilter(buffer, valid);
  } else {
    saltOut = 0;
    weightedOut = 0;
  }
}

void taskReport1(void *pvParameters);
void changeRunningMode1();

void lab32Setup() {
    StdioSerialSetup();
    buttonsSetup();

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
    pinMode(MQ2_PIN, INPUT);

    xTaskCreate(taskButtonComponent1, "TaskButton", 128, NULL, 1, NULL);
    xTaskCreate(taskUltrasonicSensor1, "TaskUltrasonic", 256, NULL, 1, NULL);
    xTaskCreate(taskGasSensor1, "TaskGas", 256, NULL, 1, NULL);
    xTaskCreate(taskReport1, "TaskReport", 256, NULL, 1, NULL);

    vTaskStartScheduler();
}

void lab32Loop() {}

void taskReport1(void *pvParameters) {
  const TickType_t xFrequency = pdMS_TO_TICKS(500);
  TickType_t xLastWakeTime = xTaskGetTickCount();
  for (;;) {
    printf("=======================\r\n");
    printf("Report:\r\n");

    printf("[GAS SENSOR]\r\n");
    printf("Raw: %d \r\n", gasSensorAnalogValue1);
    printFloat("Voltage: ", gasSensorVoltage1 / 1000.0, " V");
    printFloat("Medium: ", gasMedium, "");
    printFloat("Weighted Avg : ", gasWeighted, "");

    printf("[ULTRASONIC SENSOR]\r\n");
    printf("Duration: %ld mks\r\n", ultrasonicSensorDuration1);
    printf("Distance raw: %d cm\r\n", ultrasonicSensorDistance1);
    printFloat("Medium: ", distMedium, " cm");
    printFloat("Weighted Avg : ", distWeighted, " cm");

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

void changeRunningMode1() {
  runningMode1++;
  if (runningMode1 >= 4) 
  {
    runningMode1 = 0;
  }
  switch (runningMode1) {
    case 0:
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_GREEN_PIN, LOW);
      gasSensorAnalogValue1 = 0;
      gasSensorVoltage1 = 0;
      ultrasonicSensorDuration1 = 0;
      ultrasonicSensorDistance1 = 0;
      gasMedium = gasWeighted = 0;
      distMedium = distWeighted = 0;
      bufferIndexGas = bufferIndexDist = 0;
      bufferFilledGas = bufferFilledDist = false;
      for (int i = 0; i < BUFFER_SIZE; i++) {
        gasBuffer[i] = 0;
        distanceBuffer[i] = 0;
      }
      break;
    case 1:
      digitalWrite(LED_RED_PIN, HIGH);
      digitalWrite(LED_GREEN_PIN, LOW);
      gasSensorAnalogValue1 = 0;
      gasSensorVoltage1 = 0;
      gasMedium = gasWeighted = 0;
      bufferIndexGas = 0;
      bufferFilledGas = false;
      for (int i = 0; i < BUFFER_SIZE; i++) gasBuffer[i] = 0;
      break;
    case 2:
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_GREEN_PIN, HIGH);
      ultrasonicSensorDuration1 = 0;
      ultrasonicSensorDistance1 = 0;
      distMedium = distWeighted = 0;
      bufferIndexDist = 0;
      bufferFilledDist = false;
      for (int i = 0; i < BUFFER_SIZE; i++) distanceBuffer[i] = 0;
      break;
    case 3:
      digitalWrite(LED_RED_PIN, HIGH);
      digitalWrite(LED_GREEN_PIN, HIGH);
      break;
  }
}

