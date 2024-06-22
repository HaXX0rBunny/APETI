#pragma once

#include "cprocessing.h"

enum {
	platform = 0,
	enemy = 1,
	heal = 2
};
struct Platform
{

	CP_Vector Pos;
	CP_Vector velocity;
	float w;
	float h;

	CP_Color color;

	int removability;
	int exist;
	int objecType;
	int hitcount;

};

void Initialize_Platform(struct Platform* platform, float x, float y, float w, float h, CP_Color color, int removability, int exist, int objecType, int hitcount);

int Platform_MouseIn(struct Platform* platform);