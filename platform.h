#pragma once

#include "cprocessing.h"

enum {
	platform = 0,
	enemy = 1,
	heal = 2,
	door = 3,
	Boss1 = 4,
	Boss2 = 5,
	Boss3 = 6,
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
	int moveSpeed;
};

void Initialize_Platform(struct Platform* platform, float x, float y, float w, float h, CP_Color color, int removability, int exist, int objecType, int hitcount, int moveSpeed);

int Platform_MouseIn(struct Platform* platform);