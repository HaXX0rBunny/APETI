#include "player.h"
#include "dashEffect.h"
#include "bomb.h"
#include "gameOver.h"
#include <stdio.h>
#include "game.h"
#define PLAYER_GFORCE -1200.f
#define MAX_DASH_TIMER 0.15f
#define MAX_DASH_COOLDOWN 3.f

enum
{
	DASH_SPEED = 2000,
	MOVE_SPEED = 300,
	JUMP_SPEED = 650
};

#define DAMAGE_COOLDOWN_TIME 1.0f  // 1초 쿨다운
struct Player player;

extern struct Platform platformList[MAX_PLATFORM_LIST_SIZE];

extern const int window_width;
extern const int window_height;
float facingDirection = 1;

void Player_Init(int health, float x, float y)
{
	if (health != -1)
		player.health = health;

	player.maxHealth = 10;

	player.Pos.x = x;
	player.Pos.y = y;

	player.w = 30;
	player.h = 30;

	player.Velocity.x = 0;
	player.Velocity.y = 0;

	player.Acceleration.x = 0;
	player.Acceleration.y = 0;

	player.isGrounded = 0;

	player.isDash = 0;
	player.isDashCooldown = 0;
	player.dashTimer = 0;
	player.dashCooldown = 0;

	player.SpeedX = MOVE_SPEED;
	player.maxDashTimer = MAX_DASH_TIMER;
	player.maxDashCooldown = MAX_DASH_COOLDOWN;

	player.color = CP_Color_Create(255, 0, 0, 255);
	player.stunDuration = 0.0f;
}

void Player_ReduceHealth(int value) {
	if (player.damageCooldown <= 0.0f&& player.health >=1) {  // 쿨다운 중이 아니면 체력 감소
		player.health -= value;
		player.stunDuration = 0.5f;
		player.damageCooldown = DAMAGE_COOLDOWN_TIME;  // 쿨다운 시간 설정

		if (player.health <= 0) {
			Player_Dead();
		}
	}
}
void Player_Heal() {
	if (player.health >0&& 10>player.health)
		player.health = 10;
	

}

void Player_Ability_Init(int bomb, int dash)
{
	player.bombable = bomb;
	player.dashable = dash;
}
void Player_AddHealth(int value)
{
	player.health += value;

	if (player.health > player.maxHealth) player.maxHealth = player.health;
	if (player.health <= 0) Player_Dead();
}

void Player_Jump()
{
	if (CP_Input_KeyTriggered(KEY_W))
	{
		if (player.isGrounded)
		{
			player.isGrounded = 0;
			player.Pos.y -= 1;
			player.Velocity.y = -JUMP_SPEED;
		}
	}
}

void Player_Dash(float t)
{
	if (CP_Input_KeyTriggered(KEY_SPACE) && !player.isDashCooldown && player.dashable)
	{
		player.isDash = 1;
		player.isDashCooldown = 1;
	}

	if (player.isDash) {
		player.SpeedX = DASH_SPEED;
		player.dashTimer += t;
		if (player.dashTimer > player.maxDashTimer)
		{
			player.dashTimer = 0;
			player.SpeedX = MOVE_SPEED;
			player.isDash = 0;
		}
	}

	if (player.isDashCooldown)
	{
		player.dashCooldown += t;
		if (player.dashCooldown > player.maxDashCooldown)
		{
			player.dashCooldown = 0;
			player.isDashCooldown = 0;
		}
	}
}

void Player_Move()
{
	struct Platform dir[4];
	Collision_Player_Platform(dir);

	if (CP_Input_KeyTriggered(KEY_L) && player.bombable) {
		Player_ThrowBomb();
	}
	if (CP_Input_KeyTriggered(KEY_K)) {
		Player_Shoot();
	}
	
	if (CP_Input_KeyDown(KEY_A) && !dir[Right].exist)
	{
		player.Velocity.x = -player.SpeedX;
		facingDirection = -1; // Facing left


	}
	if (dir[Right].exist && player.Velocity.x < 0)
	{
		player.Velocity.x = 0;
		player.Pos.x = dir[Right].Pos.x + dir[Right].w;
	}

	if (CP_Input_KeyDown(KEY_D) && !dir[Left].exist)
	{
		player.Velocity.x = player.SpeedX;
		facingDirection = 1;
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
}

void Player_Dead()
{
	CP_Engine_SetNextGameState(GameOver_init, GameOver_update, GameOver_exit);
}

void Player_Update()
{
	float t = CP_System_GetDt();
	if (player.stunDuration > 0) {
		player.stunDuration -= t;
		if (player.stunDuration < 0) {
			player.stunDuration = 0;
		}
	}
	if(player.stunDuration==0){
		Player_Dash(t);
		Player_Move();
		Player_Jump();
	}
	else {
		// 스턴 상태에서는 속도 0
		player.Velocity = CP_Vector_Set(0, 0);
	}
	if (player.damageCooldown > 0.0f) {
		player.damageCooldown -= t;
	}
	player.Pos.x += player.Velocity.x * t;
	player.Pos.y += player.Velocity.y * t;

	CP_Settings_Translate(-player.Pos.x + (window_width / 2), -player.Pos.y + (window_height / 2));
}

void Player_Draw()
{

	if (player.isDash)
		Dash_Effect(player.color, &player.Pos, &player.Velocity, player.w, player.h, 3, 0.015f);
	if (player.stunDuration > 0) {
		// 스턴 상태일 때 반짝이게 하기
		static float blinkTimer = 0;
		blinkTimer += CP_System_GetDt();
		if ((int)(blinkTimer * 10) % 2 == 0) {
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));  // 빨간색
		}
		else {
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));  // 흰색
		}
	}
	else
	{
		CP_Settings_Fill(player.color);
	}

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
			switch (platform.objecType)
			{
			case Boss1:
				Remove_Platform(&platformList[i]);
				Enter_Boss1();
				break;
			case Boss2:
				Remove_Platform(&platformList[i]);
				Enter_Boss2();
				break;
			case Boss3:
				Remove_Platform(&platformList[i]);
				Enter_Boss3();
				break;
			case enemy:
				Player_ReduceHealth(1);
				break;
			case heal:
				Player_Heal(); Remove_Platform(&platformList[i]);
				break;
			case door: 
				Remove_Platform(&platformList[i]);
				break;
		
			}
		}

		if (CollisionIntersection_RectRect(player.Pos.x + (player.w / 6), player.Pos.y + player.h, player.w / 3, 1,
			platformX, platformY, platformW, platformH) && !dir[Down].exist)
		{
			dir[Down] = platform;

			switch (platform.objecType)
			{
			case Boss1:
				Enter_Boss1();
				break;
			case Boss2:
				Enter_Boss2();
				break;
			case Boss3:
				Enter_Boss3();
				break;
			case enemy:
				Player_ReduceHealth(1);
				break;
			case heal:
				Player_Heal(); Remove_Platform(&platformList[i]);
				break;
			case door:
				Remove_Platform(&platformList[i]);
				break;
			
			}
		}

		if (CollisionIntersection_RectRect(player.Pos.x, player.Pos.y, 1, player.h / 3,
			platformX, platformY, platformW, platformH) && !dir[Right].exist)
		{
			dir[Right] = platform;

			switch (platform.objecType)
			{
			case Boss1:
				Enter_Boss1();
				break;
			case Boss2:
				Enter_Boss2();
				break;
			case Boss3:
				Enter_Boss3();
				break;
			case enemy:
				Player_ReduceHealth(1);
				break;
			case heal:
				Player_Heal(); Remove_Platform(&platformList[i]);
				break;
			case door:
				Remove_Platform(&platformList[i]);
				break;
		
			}
		}

		if (CollisionIntersection_RectRect(player.Pos.x + player.w - 1, player.Pos.y, 1, player.h / 3,
			platformX, platformY, platformW, platformH) && !dir[Left].exist)
		{
			dir[Left] = platform;

			switch (platform.objecType)
			{
			case Boss1:
				Enter_Boss1();
				break;
			case Boss2:
				Enter_Boss2();
				break;
			case Boss3:
				Enter_Boss3();
				break;
			case enemy:
				Player_ReduceHealth(1);
				break;
			case heal:
				Player_Heal(); Remove_Platform(&platformList[i]);
				break;
			case door:
				Remove_Platform(&platformList[i]);
				break;
		
			}
		}
	}
}

void Player_Shoot() {
	CP_Vector bulletVelocity = { 1500*facingDirection, 0 }; // 오른쪽으로 300의 속도

	for (int i = 0; i < MAX_BULLETS; i++) {
		if (!bullets[i].active) {
			Bullet_Init(i, player.Pos, bulletVelocity, 5, CP_Color_Create(255, 255, 0, 255));
			break;
		}
	}
}

void Player_ThrowBomb() {
	float initialSpeed = 300.0f;
	CP_Vector bombVelocity = { initialSpeed * facingDirection, -initialSpeed };  // 포물선을 그리도록 초기 속도 설정

	for (int i = 0; i < MAX_BOMBS; i++) {
		if (!bombs[i].active) {
			Bomb_Init(i, player.Pos, bombVelocity, 10, CP_Color_Create(255, 0, 0, 255));
			return;
		}
	}
}
