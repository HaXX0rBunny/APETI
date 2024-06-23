#pragma once
#include "cprocessing.h"
#include "player.h"

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

	CP_Color color;
	int active;
	float hitCooldown;
};
void check_collision_sanic(struct Sanic* sanic, struct Player* player);
void Sanic_Init(float x, float y, float w, float h, int health, int damage);
void Sanic_Init_Des();
void Sanic_Move();
void Sanic_Dead();
int Sanic_Hit();
int Sanic_Stun();
void Sanic_Draw();
void Sanic_Update();