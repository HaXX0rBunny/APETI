#pragma once

#include "map.h"
#include "gravity.h"
#include "bullet.h" 
#include "bomb.h"

struct Player {
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
void Player_Shoot(); // Function to shoot bullets
void Player_ThrowBomb();  // 명확하게 void 반환 유형을 명시

void Collision_Player_Platform(struct Platform dir[4]);
