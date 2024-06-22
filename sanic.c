#include "sanic.h"
#include "player.h"
#include "dashEffect.h"
#include <math.h>

#define BLUE CP_Color_Create(0, 0, 255, 255)
#define RED CP_Color_Create(255, 0, 0, 255)
#define ACCELERATION_SPEED 10.f
#define MOVE_SPEED_LIMIT 1000.f
#define VELOCITY_LIMIT 50.f
#define TWINKLE_SPEED 2.f
#define MAX_STUN_TIMER 5.f

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

	sanic.state = 1;

	sanic.color = BLUE;
}

void Sanic_Init_Des()
{
	int r = CP_Random_RangeInt(1, 3);

	if (r == 1) 
	{
		sanic.des.x = player.Pos.x + ((player.Pos.x - sanic.pos.x) * -0.8f);
		sanic.des.y = player.Pos.y + (player.Pos.y - sanic.pos.y);
	}
	else
	{
		sanic.des.x = player.Pos.x + ((player.Pos.x - sanic.pos.x) * CP_Random_RangeFloat(-0.1f, 0.5f));
		sanic.des.y = player.Pos.y + ((player.Pos.y - sanic.pos.y) * CP_Random_RangeFloat(-0.1f, 0.5f));
	}
}

void Sanic_Move()
{
	float t = CP_System_GetDt();

	if ((sanic.velocity.x < VELOCITY_LIMIT && sanic.velocity.x > -VELOCITY_LIMIT) 
		|| (sanic.velocity.y < VELOCITY_LIMIT && sanic.velocity.y > -VELOCITY_LIMIT))
		Sanic_Init_Des();

	float accX = (sanic.des.x - sanic.pos.x) * ACCELERATION_SPEED;
	float accY = (sanic.des.y - sanic.pos.y) * ACCELERATION_SPEED;

	sanic.acceleration.x = accX;
	sanic.acceleration.y = accY;

	if (sanic.velocity.x > MOVE_SPEED_LIMIT) sanic.velocity.x = MOVE_SPEED_LIMIT;
	if (sanic.velocity.y > MOVE_SPEED_LIMIT) sanic.velocity.y = MOVE_SPEED_LIMIT;
	if (sanic.velocity.x < -MOVE_SPEED_LIMIT) sanic.velocity.x = -MOVE_SPEED_LIMIT;
	if (sanic.velocity.y < -MOVE_SPEED_LIMIT) sanic.velocity.y = -MOVE_SPEED_LIMIT;

	sanic.velocity.x += sanic.acceleration.x * t;
	sanic.velocity.y += sanic.acceleration.y * t;

	sanic.pos.x += sanic.velocity.x * t;
	sanic.pos.y += sanic.velocity.y * t;
}

void Sanic_Attack()
{

}

int Sanic_Hit()
{
	
	return 0;
}

int Sanic_Stun()
{
	static float rot_counter = 0;
	static float stunTimer = 0;

	float t = CP_System_GetDt();

	rot_counter += rot_counter >= 1.0f ? -1.f : t * TWINKLE_SPEED;
	sanic.color = CP_Color_Lerp(BLUE, RED, rot_counter);

	stunTimer += t;

	if (stunTimer > MAX_STUN_TIMER)
	{
		sanic.color = BLUE;
		stunTimer = 0;
		return 1;
	}
	
	return 0;
}

void Sanic_Draw()
{
	Dash_Effect(sanic.color, &sanic.pos, &sanic.velocity, sanic.w, sanic.h, 5, 0.03f);
	CP_Settings_Fill(sanic.color);
	CP_Graphics_DrawRect(sanic.pos.x, sanic.pos.y, sanic.w, sanic.h);
}

void Sanic_Update()
{
	switch (sanic.state)
	{
	case 0:
		Sanic_Move();
		Sanic_Attack();
		if (Sanic_Hit())
		{
			sanic.state = 1;
		}
		break;
	case 1:
		if (Sanic_Stun())
		{
			sanic.state = 0;
		}
		break;
	}
}