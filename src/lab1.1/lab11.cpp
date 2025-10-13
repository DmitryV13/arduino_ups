// #include "lab11.h"

// void lab11Setup(void)
// {
//     StdioSerialSetup();
//     pinMode(LED_PIN, OUTPUT);
    
//     ledOff(LED_PIN);

//     printf("System ready. Available commands: 'led on', 'led off'.\n");
// }

// void lab11Loop(void)
// {
//     char buffer[32];

//     if (fgets(buffer, sizeof(buffer), stdin) == NULL)
//     {
//         return;
//     }

//     buffer[strcspn(buffer, "\r\n")] = '\0';

//     if (strcmp(buffer, "led on") == 0)
//     {
//         ledOn(LED_PIN);
//         printf("LED is ON\n");
//     }
//     else if (strcmp(buffer, "led off") == 0)
//     {
//         ledOff(LED_PIN);
//         printf("LED is OFF\n");
//     }
//     else
//     {
//         printf("Unknown command\n");
//     }
// }