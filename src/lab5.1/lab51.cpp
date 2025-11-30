#include "lab51.h"

float setPoint = 25.0;
float hysteresis = 2.0;
float currentTemp = 0.0;
bool relayState = false;

void controlHeater();
float readTemperature();
void updateDisplay();
void processCommands4();


void lab51Setup()
{
    StdioSerialSetup();
    relaySetup(RELAY_PIN1);
    lcdSetup();
}

void lab51Loop()
{
    currentTemp = readTemperature();
    controlHeater();
    updateDisplay();
    processCommands4();

    Serial.print(currentTemp);
    Serial.print(",");
    Serial.println(setPoint);

    delay(500);
}

float readTemperature()
{
    int raw = analogRead(TMP_PIN);
    float voltage = raw * (5.0 / 1023.0);
    float tempC = (voltage - 0.5) * 100.0;
    return tempC;
}

void controlHeater()
{
    if (currentTemp < setPoint - hysteresis / 2)
    {
        relayState = true;
        relayOpen();
    }
    else if (currentTemp > setPoint + hysteresis / 2)
    {
        relayState = false;
        relayClose();
    }
}

void updateDisplay()
{
    lcdSetCursor(0, 0);
    lcdPrint("Temp:");
    lcdPrint(currentTemp, 1);
    lcdPrint("C    ");

    lcdSetCursor(0, 1);
    lcdPrint("Set:");
    lcdPrint(setPoint, 1);
    lcdPrint("C ");
    lcdPrint(relayState ? "ON " : "OFF");
}

void processCommands4()
{
    if (stdioHasData())
    {
        String command = stdioGetString();
        command.trim();

        if (command.startsWith("SET"))
        {
            setPoint = command.substring(3).toFloat();
            printFloat("SetPoint updated: ", setPoint, "");
        }
        else if (command.startsWith("HYS"))
        {
            hysteresis = command.substring(3).toFloat();
            printFloat("Hysteresis updated: ", hysteresis, "");
        }
        else
        {
            printf("Unknown command. Use:");
            printf("SET <value> or HYS <value>");
        }
    }
}