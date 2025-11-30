#include "lab62.h"

// Время сигналов (мс)
const TickType_t BLINK_INTERVAL = 500 / portTICK_PERIOD_MS;

// Флаг пешеходного запроса
volatile bool pedestrianRequest = false;

// Текущее состояние
int currentState4 = 0;

// ------------------ Семафор для синхронизации ------------------
SemaphoreHandle_t stateSemaphore;

// ------------------ Функции управления светодиодами ------------------
void setCar(SState s)
{
    digitalWrite(CAR_RED_PIN, s == RED);
    digitalWrite(CAR_YELLOW_PIN, s == YELLOW);
    digitalWrite(CAR_GREEN_PIN, s == GREEN);
}

void setHuman(SState s)
{
    digitalWrite(PED_RED_PIN, s == RED);
    digitalWrite(PED_GREEN_PIN, s == GREEN);
}

// ------------------ Задача FSM ------------------
void TaskFSM(void *pvParameters)
{
    for (;;)
    {
        if (!pedestrianRequest)
        {
            // Обычный режим: EW зелёный, NS красный
            setCar(GREEN);
            setHuman(RED);
            vTaskDelay(100 / portTICK_PERIOD_MS); // небольшая задержка для плавности
        }
        else
        {
            State1 s = fsm1[currentState4];

            // Управление машинным светофором
            setCar(s.car);

            // Управление пешеходным
            if (s.blink == BLINK_S)
            {
                TickType_t elapsed = 0;
                while (elapsed < s.delayTime)
                {
                    setHuman(s.human);
                    vTaskDelay(BLINK_INTERVAL);
                    setHuman(EMPTY);
                    vTaskDelay(BLINK_INTERVAL);
                    elapsed += 2 * BLINK_INTERVAL;
                }
            }
            else
            {
                setHuman(s.human);
                vTaskDelay(s.delayTime);
            }

            // Сообщаем задаче вывода о новом состоянии
            xSemaphoreGive(stateSemaphore);

            // Переход в следующее состояние
            currentState4 = s.nextState;
            if (currentState4 == 0)
            {
                pedestrianRequest = false;
            }
        }
    }
}

void TaskButton(void *pvParameters)
{
    for (;;)
    {
        if (digitalRead(BUTTON_PED_PIN) == LOW)
        {
            pedestrianRequest = true;
        }
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

// ------------------ Задача для вывода состояния ------------------
void TaskPrint(void *pvParameters)
{
    for (;;)
    {
        // Ждём, пока FSM обновит состояние
        if (xSemaphoreTake(stateSemaphore, portMAX_DELAY) == pdTRUE)
        {
            State1 s = fsm1[(currentState4 == 0 ? 4 : currentState4 - 1)]; // выводим предыдущее завершённое состояние

            printf("FSM State: ");
            printf("%d", currentState4);
            printf(" | Car: ");
            if (s.car == GREEN)
            {
                printf("GREEN");
            }
            else if (s.car == YELLOW)
            {
                printf("YELLOW");
            }
            else
            {
                printf("RED");
            }

            printf(" | Pedestrian: ");
            if (s.human == GREEN)
            {
                printf("GREEN");
            }
            else
            {
                printf("RED");
            }

            printf(" | Blink: ");
            if (s.blink == BLINK_S)
            {
                printf("YES");
            }
            else
            {
                printf("NO");
            }

            printf("/n");
        }
    }
}

// ------------------ Setup ------------------
void lab62Setup()
{
    StdioSerialSetup();

    ledSetup(CAR_RED_PIN);
    ledSetup(CAR_YELLOW_PIN);
    ledSetup(CAR_GREEN_PIN);

    ledSetup(PED_RED_PIN);
    ledSetup(PED_GREEN_PIN);

    pinMode(BUTTON_PED_PIN, INPUT_PULLUP);

    // Создаём семафор
    stateSemaphore = xSemaphoreCreateBinary();

    xTaskCreate(TaskFSM, "FSM", 256, NULL, 1, NULL);
    xTaskCreate(TaskButton, "Button", 128, NULL, 2, NULL);
    xTaskCreate(TaskPrint, "Print", 256, NULL, 1, NULL);

    vTaskStartScheduler();
}

void lab62Loop()
{
    // пустой
}
