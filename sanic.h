#pragma once
#include "cprocessing.h"

struct Sanic
{
	CP_Vector pos;

	int health;
	int damage;

	float w;
	float h;

	int state;

	CP_Vector velocity;
	CP_Vector acceleration;
	CP_Vector des;
};

void Sanic_Init(float x, float y, float w, float h, int health, int damage);

CP_Vector Sanic_Init_Chasing_Des();
CP_Vector Sanic_Init_Starting_Des();

int Sanic_Move_To_Des();
int Sanic_Move_To_Des_Resist();

void Sanic_Draw();
void Sanic_Update();