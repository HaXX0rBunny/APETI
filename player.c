#include "player.h"

#define PLAYER_GFORCE -500.f

struct Player player = { 100, 100, 30, 30, 0, 0, 0, 0, 0, 0, 0, {255, 0, 0, 255} };
extern struct Platform platformList[MAX_PLATFORM_LIST_SIZE];

void Player_Jump(float initV)
{
	if (player.isGrounded)
	{
		player.isGrounded = 0;
		player.Pos.y -= 1;
		player.Velocity.y = initV;
	}
}

void Player_AddHealth(int value)
{
	player.health += value;

	if (player.health > player.maxHealth) player.maxHealth = player.health;
	if (player.health <= 0) Player_Dead();
}

void Player_Dead()
{

}

void Player_Update()
{
	float t = CP_System_GetDt();

	struct Platform dir[4];
	Collision_Player_Platform(dir);

	if (CP_Input_KeyDown(KEY_A) && !dir[Right].exist)
	{
		player.Velocity.x = -300;
	}
	if (dir[Right].exist && player.Velocity.x < 0)
	{
		player.Velocity.x = 0;
		player.Pos.x = dir[Right].Pos.x + dir[Right].w;
	}

	if (CP_Input_KeyDown(KEY_D) && !dir[Left].exist)
	{
		player.Velocity.x = 300;
	}
	if (dir[Left].exist && player.Velocity.x > 0)
	{
		player.Velocity.x = 0;
		player.Pos.x = dir[Left].Pos.x - player.w;
	}

	if (CP_Input_KeyReleased(KEY_A) || CP_Input_KeyReleased(KEY_D))
	{
		player.Velocity.x = 0;
	}

	if (!dir[Down].exist)
	{
		Calculate_Gravity(&player.Velocity.y, &player.Acceleration.y, PLAYER_GFORCE);
		player.isGrounded = 0;
	}
	else
	{
		player.Velocity.y = 0;
		player.isGrounded = 1;
		if (!dir[Right].exist && !dir[Left].exist)
			player.Pos.y = dir[Down].Pos.y - player.h;
	}

	if (dir[Up].exist && player.Velocity.y <= 0)
	{
		player.Velocity.y = 0;
	}

	if (CP_Input_KeyTriggered(KEY_W))
	{
		Player_Jump(-300.f);
	}

	player.Pos.x = player.Pos.x + player.Velocity.x * t;
	player.Pos.y = player.Pos.y + player.Velocity.y * t;
}

void Player_Draw()
{
	CP_Settings_Fill(player.color);
	CP_Graphics_DrawRect(player.Pos.x, player.Pos.y, player.w, player.h);
}

void Collision_Player_Platform(struct Platform dir[4])
{
	int i = 0;

	for (i = 0; i < 4; i++)
		dir[i].exist = 0;

	for (i = 0; i < MAX_PLATFORM_LIST_SIZE; i++)
	{
		if (!platformList[i].exist)
			continue;

		struct Platform platform = platformList[i];
		float platformX = platform.Pos.x;
		float platformY = platform.Pos.y;
		float platformW = platform.w;
		float platformH = platform.h;

		if (CollisionIntersection_RectRect(player.Pos.x + (player.w / 6), player.Pos.y, player.w / 3, 1,
			platformX, platformY, platformW, platformH) && !dir[Up].exist)
		{
			dir[Up] = platform;
		}

		if (CollisionIntersection_RectRect(player.Pos.x + (player.w / 6), player.Pos.y + player.h, player.w / 3, 1,
			platformX, platformY, platformW, platformH) && !dir[Down].exist)
		{
			dir[Down] = platform;
		}

		if (CollisionIntersection_RectRect(player.Pos.x, player.Pos.y, 1, player.h / 3,
			platformX, platformY, platformW, platformH) && !dir[Right].exist)
		{
			dir[Right] = platform;
		}

		if (CollisionIntersection_RectRect(player.Pos.x + player.w - 1, player.Pos.y, 1, player.h / 3,
			platformX, platformY, platformW, platformH) && !dir[Left].exist)
		{
			dir[Left] = platform;
		}
	}
}