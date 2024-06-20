#pragma once

#include "cprocessing.h"

enum {
	platform = 0,
	Enemy = 1
};
struct Platform
{

	CP_Vector Pos;

	float w;
	float h;

	CP_Color color;

	int removability;
	int exist;
	int objecType;
};

void Initialize_Platform(struct Platform* platform, float x, float y, float w, float h, CP_Color color, int removability, int exist);

int Platform_MouseIn(struct Platform* platform);