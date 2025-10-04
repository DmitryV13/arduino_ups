#include "lab11.h"

void lab11_setup(void)
{
    StdioSerialInit();

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    printf("System ready. Available commands: 'led on', 'led off'.\n");
}

void lab11_loop(void)
{
    char buffer[32];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return;
    }

    buffer[strcspn(buffer, "\r\n")] = '\0';

    if (strcmp(buffer, "led on") == 0)
    {
        digitalWrite(LED_PIN, HIGH);
        printf("LED is ON\n");
    }
    else if (strcmp(buffer, "led off") == 0)
    {
        digitalWrite(LED_PIN, LOW);
        printf("LED is OFF\n");
    }
    else
    {
        printf("Unknown command\n");
    }
}