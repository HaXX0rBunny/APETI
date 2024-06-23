#pragma once

#include "cprocessing.h"

enum
{
	BODY_COL = 3,
	BODY_ROW = 5
};

struct Body
{
	CP_Vector pos;
	CP_Vector start;
	CP_Vector end;

	float w;
	float h;

	CP_Color color;
};

void Body_Init(struct Body* body, float x, float y, float desX, float desY, float w, float h, CP_Color color);
void Body_Draw(struct Body* body);
int Body_Attack(struct Body* body);

struct Demon
{
	int health;
	int damage;
	float hitCooldown;
	struct Body body[BODY_COL * BODY_ROW];

	int eye;
	int isAttack;
};

void Demon_Init(float x, float y, float desX, float desY, float w, float h, int health, int damage);

int Demon_Summon();

int Demon_Selete_Body(int* cnt);
int Demon_Attack_Cooldown();
int Demon_Attack();

void Demon_Hit();
void Demon_Dead();

void Demon_Twinkle_Eye(int isOpen);
void Demon_Next_Eye();

void Demon_Draw();
void Demon_Update();