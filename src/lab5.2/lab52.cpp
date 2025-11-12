#include "lab52.h"

// Constants for Motor Driver
const int motorEnablePin = 6; // Enable pin for PWM speed control
const int motorPin1 = 5;      // Input 1 for direction
const int motorPin2 = 4;      // Input 2 for direction

// PID parameters
float kp = 0.3;
float td = 0.0;
float ti = 90.0;

// Error array
int error[3] = {0, 0, 0};
// Voltage array
int u[2] = {0, 0};
// delay
int T = 10;

const float MAX_RPM = 3000.0;
float realSpeedRpm = 0;

int sat(int s, int lb, int ub);
int pidAntiWindUp(int e0, int e1, int e2, int u1, int lb, int ub, float T);
float getMotorRPM();
void processCommands2();

void lab52Setup()
{
    lcdSetup();
    lcdPrint("System Ready");

    motorSetup(MOTOR_ENABLE_PIN, MOTOR_PIN1, MOTOR_PIN2);
}

void lab52Loop()
{
    processCommands2();
    int setpoint = (float)getSpeed() / 1023.0 * MAX_RPM; // Setpoint to RPM
    realSpeedRpm = getMotorRPM();                        // from sensor

    // PID control calculations
    error[0] = setpoint - realSpeedRpm; // first error
    u[0] = pidAntiWindUp(error[0], error[1], error[2], u[1], 0, 255, T);
    lcdPrint("PID:" + String(u[0]));
    analogWrite(motorEnablePin, u[0]);

    error[1] = error[0]; // Shifting operation
    error[2] = error[1]; // Shifting operation
    u[1] = u[0];         // Shifting operation
    delay(T);            // Sampling delay
}

void controlMotor1(int speed)
{
    if (speed == 0)
    {
        digitalWrite(motorEnablePin, LOW); // Turn motor off
        lcdSetCursor(0, 1);
        lcdPrint("Motor is OFF     ");
    }
    else
    {
        int dir = speed > 0 ? HIGH : LOW;
        digitalWrite(motorPin1, !dir);
        digitalWrite(motorPin2, dir);
        analogWrite(motorEnablePin, abs(speed)); // Set speed
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
            kp = command.substring(3).toFloat();
        }
        else if (command.startsWith("ti "))
        {
            ti = command.substring(3).toFloat();
        }
        else if (command.startsWith("td "))
        {
            td = command.substring(3).toFloat();
        }
    }
}

int pidAntiWindUp(int e0, int e1, int e2, int u1, int lb, int ub, float T)
{
    T = T / 1000;                                                              // Conversion from ms to s
    float v = sat(u1, lb, ub) - u1;  // разница между ограниченным и рассчитанным сигналом
    float u = u1 + kp * (e0 - e1 + T / ti * e0 + td / T * (e0 - 2 * e1 + e2)) + (T/ti) * v;
    u = sat(u, lb, ub);                                                        // Saturation difference
    return u;
}

// Saturation function
int sat(int s, int lb, int ub)
{
    if (s >= ub)
        return ub;
    if (s <= lb)
        return lb;
    return s;
}

float getMotorRPM()
{
    return 0.0;
}