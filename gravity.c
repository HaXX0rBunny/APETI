#include "gravity.h"

void Calculate_Gravity(float* yVel, float* yAcc, float g)
{
	float t = CP_System_GetDt();
	(*yVel) = (*yVel) - ((*yAcc) + g) * t;
}