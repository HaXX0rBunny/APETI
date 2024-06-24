#include "gravity.h"

void Calculate_Gravity(float* yVel, float g)
{
	float t = CP_System_GetDt();
	(*yVel) -= g * t;
}