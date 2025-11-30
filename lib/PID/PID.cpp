#include "PID.h"

// PID parameters
float kp = 0.3;
float td = 0.0;
float ti = 90.0;

int pidAntiWindUp(int e0, int e1, int e2, int u1, int lb, int ub, float T)
{
    T = T / 1000;                   // Conversion from ms to s
    float v = sat(u1, lb, ub) - u1; // разница между ограниченным и рассчитанным сигналом
    float u = u1 + kp * (e0 - e1 + T / ti * e0 + td / T * (e0 - 2 * e1 + e2)) + (T / ti) * v;
    u = sat(u, lb, ub); // Saturation difference
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

void setKp(float Kp)
{
    kp = Kp;
}

void setTi(float Ti)
{
    ti = Ti;
}
void setTd(float Td)
{
    td = Td;
}