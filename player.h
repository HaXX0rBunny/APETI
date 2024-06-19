#pragma once

#include "map.h"
#include "gravity.h"

struct Player
{
	int maxHealth;
	int health;

	float w;
	float h;

	CP_Vector Pos;
	CP_Vector Velocity;
	CP_Vector Acceleration;

	int isGrounded;

	CP_Color color;
};

void Player_Init();

void Player_Jump(float initV);

void Player_AddHealth(int value);
void Player_Dead();

void Player_Draw();
void Player_Update();

void Collision_Player_Platform(struct Platform dir[4]);