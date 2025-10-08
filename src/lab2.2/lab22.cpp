// #include <Arduino.h>
// #include <LiquidCrystal.h>
// #include <Arduino_FreeRTOS.h>
// #include <semphr.h>
// #include <queue.h>
// #include <stdio.h>

// #define BUTTON_PIN 9
// #define BUTTON_RESET 10
// #define LED_TASK1_PIN 3
// #define LED_TASK2_PIN 2

// LiquidCrystal lcd(13, 12, 7, 6, 5, 4);

// SemaphoreHandle_t xButtonSemaphore;
// QueueHandle_t xDataQueue;

// byte N = 0;
// bool ledTask1State = LOW;

// void taskButton(void *pvParameters);
// void taskSync(void *pvParameters);
// void taskAsync(void *pvParameters);
// void taskReset(void *pvParameters);

// static FILE *StdioStream;

// static int PutChar(char ch, FILE *f) 
// { 
//   return Serial.write(ch); 
// }

// static int GetChar(FILE *f) 
// { 
//   while (!Serial.available()); return Serial.read(); 
// }

// void StdioSerialInit(void) 
// {
//   Serial.begin(9600);
//   StdioStream = fdevopen(PutChar, GetChar);
//   stdin  = StdioStream;
//   stdout = StdioStream;
// }

// void setup() 
// {
//   StdioSerialInit();

//   pinMode(BUTTON_PIN, INPUT_PULLUP);
//   pinMode(BUTTON_RESET, INPUT_PULLUP);
//   pinMode(LED_TASK1_PIN, OUTPUT);
//   pinMode(LED_TASK2_PIN, OUTPUT);

//   xButtonSemaphore = xSemaphoreCreateBinary();
//   xDataQueue = xQueueCreate(32, sizeof(byte));

//   if (xButtonSemaphore != NULL && xDataQueue != NULL) 
//   {
//     xTaskCreate(taskButton, "Task1", 128, NULL, 1, NULL);
//     xTaskCreate(taskSync,   "Task2", 256, NULL, 1, NULL);
//     xTaskCreate(taskAsync,  "Task3", 256, NULL, 1, NULL);
//     xTaskCreate(taskReset,  "ResetTask", 256, NULL, 1, NULL);
//     xTaskCreate(taskN,  "NDisplayTask", 256, NULL, 1, NULL);
//   }

//   vTaskStartScheduler();
// }

// void loop() 
// {

// }

// void taskButton(void *pvParameters) 
// {
//   const TickType_t xFrequency = pdMS_TO_TICKS(10);
//   TickType_t xLastWakeTime = xTaskGetTickCount();
//   byte prevState = HIGH;

//   for (;;) 
//   {
//     byte currentState = digitalRead(BUTTON_PIN);
//     if (currentState == LOW && prevState == HIGH) 
//     {
//       digitalWrite(LED_TASK1_PIN, HIGH);
//       ledTask1State = HIGH;
//       vTaskDelay(pdMS_TO_TICKS(1000));
//       digitalWrite(LED_TASK1_PIN, LOW);
//       ledTask1State = LOW;

//       xSemaphoreGive(xButtonSemaphore);
//     }
//     prevState = currentState;
//     vTaskDelayUntil(&xLastWakeTime, xFrequency);
//   }
// }

// void taskSync(void *pvParameters) 
// {
//   for (;;) 
//   {
//     if (xSemaphoreTake(xButtonSemaphore, portMAX_DELAY) == pdTRUE) 
//     {
//       N++;
//       if(N >= 255)
//       {
//         N = 255;
//       }

//       for (byte i = 1; i <= N; i++) 
//       {
//         xQueueSendToBack(xDataQueue, &i, 0);
//         vTaskDelay(pdMS_TO_TICKS(50)); 
//       }

//       byte endMarker = 0;
//       xQueueSendToBack(xDataQueue, &endMarker, 0);

//       for (byte i = 0; i < N; i++) 
//       {
//         digitalWrite(LED_TASK2_PIN, HIGH);
//         vTaskDelay(pdMS_TO_TICKS(300));
//         digitalWrite(LED_TASK2_PIN, LOW);
//         vTaskDelay(pdMS_TO_TICKS(500));
//       }
//     }
//   }
// }

// void taskAsync(void *pvParameters) 
// {
//   byte receivedByte = 0;

//   for (;;) 
//   {
//     if (xQueueReceive(xDataQueue, &receivedByte, pdMS_TO_TICKS(200)) == pdTRUE) 
//     {
//       if (receivedByte == 0) 
//       {
//         printf("\n");
//       } else {
//         printf("%d ", receivedByte);
//       }
//     } else {
//       vTaskDelay(pdMS_TO_TICKS(200));
//     }
//   }
// }

// void taskReset(void *pvParameters) 
// {
//   for (;;) 
//   {
//     if (digitalRead(BUTTON_RESET) == LOW) 
//     {
//       N = 0;
//       vTaskDelay(pdMS_TO_TICKS(300));
//     }

//     vTaskDelay(pdMS_TO_TICKS(20));
//   }
// }

// void taskN(void *pvParameters) 
// {
//   for (;;) 
//   {
//     lcd.setCursor(0, 0);
//     lcd.print("N = ");         
//     lcd.print(N);
//     lcd.print("   "); 

//     vTaskDelay(pdMS_TO_TICKS(200));
//   }
// }
