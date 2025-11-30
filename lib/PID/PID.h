#ifndef PID_H
#define PID_H

// PID parameters
extern float kp;
extern float td;
extern float ti;

int pidAntiWindUp(int e0, int e1, int e2, int u1, int lb, int ub, float T);
int sat(int s, int lb, int ub);

void setKp(float Kp);
void setTi(float Ti);
void setTd(float Td);

#endif