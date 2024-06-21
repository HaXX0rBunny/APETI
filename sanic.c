#include "sanic.h"
#include "player.h"
#include <math.h>

#define BLUE CP_Color_Create(0, 0, 255, 255)
#define RED CP_Color_Create(255, 0, 0, 255)
#define DISTANCE_PADDING 0.f
#define RADIUS 30.f
#define MOVE_SPEED 10.f
#define MOVE_SPEED_LIMIT 500.f
#define MOVE_SPEED_UNDER 50.f

struct Sanic sanic;
extern struct Player player;

void Sanic_Init(float x, float y, float w, float h, int health, int damage)
{
	sanic.pos.x = x;
	sanic.pos.y = y;

	sanic.w = w;
	sanic.h = h;

	sanic.health = health;
	sanic.damage = damage;

	sanic.velocity.x = 0;
	sanic.velocity.y = 0;

	sanic.acceleration.x = 0;
	sanic.acceleration.y = 0;

	sanic.state = 0;

	sanic.des = Sanic_Init_Chasing_Des();
}

CP_Vector Sanic_Init_Chasing_Des()
{
	CP_Vector vec = { 0, 0 };

	float disX = player.Pos.x - sanic.pos.x;
	float disY = player.Pos.y - sanic.pos.y;

	vec.x = player.Pos.x + (disX * DISTANCE_PADDING);
	vec.y = player.Pos.y + (disY * DISTANCE_PADDING);

	return vec;
}

CP_Vector Sanic_Init_Starting_Des()
{
	CP_Vector vec = { 0, 0 };
	
	vec.x = CP_Random_RangeFloat(sanic.pos.x - RADIUS, sanic.pos.x + RADIUS);

	float disX = player.Pos.x - vec.x;

	vec.y = sqrtf((RADIUS * RADIUS) - (disX * disX));

	return vec;
}

int Sanic_Move_To_Des()
{
	float accX = (sanic.des.x - sanic.pos.x) * MOVE_SPEED;
	float accY = (sanic.des.y - sanic.pos.y) * MOVE_SPEED;

	if (accX > MOVE_SPEED_LIMIT) accX = MOVE_SPEED_LIMIT;
	if (accX < -MOVE_SPEED_LIMIT) accX = -MOVE_SPEED_LIMIT;
	if (accX < MOVE_SPEED_UNDER && accX > -MOVE_SPEED_UNDER) accX = MOVE_SPEED_UNDER;

	if (accY > MOVE_SPEED_LIMIT) accY = MOVE_SPEED_LIMIT;
	if (accY < -MOVE_SPEED_LIMIT) accY = -MOVE_SPEED_LIMIT;
	if (accY < MOVE_SPEED_UNDER && accY > -MOVE_SPEED_UNDER) accY = MOVE_SPEED_UNDER;

	sanic.acceleration.x = accX;
	sanic.acceleration.y = accY;

	if (fabsf(sanic.pos.x - sanic.des.x) < 5.f) return 1;

	return 0;
}

int Sanic_Move_To_Des_Resist()
{
	sanic.acceleration.x = 10;
	sanic.acceleration.y = 10;

	if (fabsf(sanic.pos.x - sanic.des.x) < 5.f) return 1;

	return 0;
}

void Sanic_Draw()
{
	CP_Settings_Fill(BLUE);
	CP_Graphics_DrawRect(sanic.pos.x, sanic.pos.y, sanic.w, sanic.h);

	CP_Settings_Fill(RED);
	CP_Graphics_DrawRect(sanic.des.x, sanic.des.y, 10, 10);
}

void Sanic_Update()
{
	float t = CP_System_GetDt();

	sanic.des = Sanic_Init_Chasing_Des();
	Sanic_Move_To_Des();

	sanic.velocity.x += sanic.acceleration.x * t;
	sanic.velocity.y += sanic.acceleration.y * t;

	sanic.pos.x += sanic.velocity.x * t;
	sanic.pos.y += sanic.velocity.y * t;
}