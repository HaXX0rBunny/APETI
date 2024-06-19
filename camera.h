#pragma once

#include "cprocessing.h"

struct Camera
{
	CP_Vector pos;
};

void Move_Camera(float x, float y);
void Update_Camera();