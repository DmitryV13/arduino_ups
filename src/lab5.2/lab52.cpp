#include "lab52.h"

const int encoderPin = 3;

// Error array
int error[3] = {0, 0, 0};
// Voltage array
int u[2] = {0, 0};
// delay
int T = 10;

const float MAX_RPM = 350.0;
float realSpeedRpm = 0;
int lastState = 0;
const int PULSES_PER_REV = 20;

volatile unsigned long pulseCount = 0;

int sat(int s, int lb, int ub);
int pidAntiWindUp(int e0, int e1, int e2, int u1, int lb, int ub, float T);
float getMotorRPM();
void processCommands2();
void encoderISR();

void lab52Setup()
{
    lcdSetup();
    lcdPrint("System Ready");

    motorSetup(MOTOR_ENABLE_PIN, MOTOR_PIN1, MOTOR_PIN2);

    pinMode(encoderPin, INPUT);
    lastState = digitalRead(encoderPin);
    attachInterrupt(digitalPinToInterrupt(encoderPin), encoderISR, RISING);
}

void lab52Loop()
{
    processCommands2();
    int setpoint = (float)getSpeed() / 1023.0 * MAX_RPM; // Setpoint to RPM
    realSpeedRpm = getMotorRPM();                        // from sensor

    // PID control calculations
    error[0] = setpoint - realSpeedRpm; // first error
    u[0] = pidAntiWindUp(error[0], error[1], error[2], u[1], 0, 255, T);
    lcdSetCursor(0, 0);
    lcdPrint("PID:" + String(u[0]));
    lcd.print("        ");
    setAbsoluteSpeed(u[0]);

    error[1] = error[0]; // Shifting operation
    error[2] = error[1]; // Shifting operation
    u[1] = u[0];         // Shifting operation
    delay(T);            // Sampling delay
}

void controlMotor1(int speed)
{
    setSpeed(speed);
    if (speed == 0)
    {
        motorTurnOff();
        lcdSetCursor(0, 1);
        lcdPrint("Motor is OFF     ");
    }
    else
    {
        lcdSetCursor(0, 1);
        lcdPrint("Motor Speed:" + String(speed));
    }
}

void processCommands2()
{
    if (stdioHasData())
    {
        String command = stdioGetString();
        command.trim();
        if (command.startsWith("speed "))
        {
            // Extract speed from command
            int speed = command.substring(6).toInt();
            // Will use only one direction
            if (speed < 0)
            {
                speed = 0;
            }
            controlMotor1(map(speed, -100, 100, -255, 255)); // Map from -100-100 to -255-255 PWM range
        }
        else if (command.startsWith("kp "))
        {
            setKp(command.substring(3).toFloat());
        }
        else if (command.startsWith("ti "))
        {
            setTi(command.substring(3).toFloat());
        }
        else if (command.startsWith("td "))
        {
            setTd(command.substring(3).toFloat());
        }
    }
}

float getMotorRPM()
{
    static unsigned long lastCount = 0;
    static float rpm = 0;

    unsigned long count = pulseCount - lastCount;
    lastCount = pulseCount;

    rpm = (count / float(PULSES_PER_REV)) * (60.0 / (T / 1000.0)); // T = задержка цикла
    return rpm;
}

void encoderISR()
{
    pulseCount++;
}
