#pragma once
#include "cprocessing.h"

struct Enemy
{
	CP_Vector Pos;

	float w;
	float h;

	CP_Color color;

	int removability;
	int exist;
};

void Initialize_Enemy(struct Enemy* Enemy, float x, float y, float w, float h, CP_Color color, int removability, int exist);

int Enemy_MouseIn(struct Enemy* Enemy);