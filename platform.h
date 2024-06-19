#pragma once

#include "cprocessing.h"

struct Platform
{
	CP_Vector Pos;

	float w;
	float h;

	CP_Color color;

	int removability;
	int exist;
};

void Initialize_Platform(struct Platform* platform, float x, float y, float w, float h, CP_Color color, int removability, int exist);

int Platform_MouseIn(struct Platform* platform);