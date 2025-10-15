#include "lab31.h"

int gasSensorAnalogValue = 0;
int gasSensorVoltage = 0;

int ultrasonicSensorDuration = 0;
int ultrasonicSensorDistance = 0;

byte runningMode = 0;

void taskReport(void *pvParameters);

void changeRunningMode();

void lab31Setup() 
{
  StdioSerialSetup();
  buttonsSetup();

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  pinMode(MQ2_PIN, INPUT);

  xTaskCreate(taskButtonComponent, "TaskButton", 128, NULL, 1, NULL);
  xTaskCreate(taskUltrasonicSensor,   "TaskUltrasonic", 256, NULL, 1, NULL);
  xTaskCreate(taskGasSensor,  "TaskGas", 256, NULL, 1, NULL);
  xTaskCreate(taskReport,  "TaskReport", 256, NULL, 1, NULL);

  vTaskStartScheduler();
}

void lab31Loop() 
{

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
      ledOff(LED_RED_PIN);
      ledOff(LED_GREEN_PIN);
      gasSensorAnalogValue = 0;
      gasSensorVoltage = 0;
      ultrasonicSensorDuration = 0;
      ultrasonicSensorDistance = 0;
      break;
    }
    case 1:
    {
      ledOn(LED_RED_PIN);
      ledOff(LED_GREEN_PIN);
      gasSensorAnalogValue = 0;
      gasSensorVoltage = 0;
      break;
    }
    case 2:
    {
      ledOff(LED_RED_PIN);
      ledOn(LED_GREEN_PIN);
      ultrasonicSensorDuration = 0;
      ultrasonicSensorDistance = 0;
      break;
    }
    case 3:
    {
      ledOn(LED_RED_PIN);
      ledOn(LED_GREEN_PIN);
      break;
    }
  }
}