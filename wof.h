#pragma once

#include "cprocessing.h"

struct WofEye
{
	CP_Vector pos;

	int damage;

	float w;
	float h;

	int isOpen;

	CP_Color eyeCover_color;
	CP_Color color;
};

void WofEye_Init(struct WofEye* wofEye, float x, float y, float w, float h, int damage);

void WofEye_Attack(struct WofEye* wofEye);
int WofEye_Hit(struct WofEye* wofEye);

int WofEye_Open(struct WofEye* wofEye);
int WofEye_Close(struct WofEye* wofEye);

void WofEye_Draw(struct WofEye* wofEye);

struct Wof
{
	CP_Vector pos;

	int health;

	float w;
	float h;

	struct WofEye eye[3];

	int state;

	CP_Color color;
};

void Wof_Init(float x, float y, float w, float h, int health, int damage);

void Wof_Hit();

void Wof_Create_Wall();

int Wof_Timer();
int Wof_Selete_Eye();

void Wof_Draw();
void Wof_Update();