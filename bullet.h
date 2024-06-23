#pragma once
#include "map.h"
#include "cprocessing.h"

#define MAX_BULLETS 100

typedef struct {
    CP_Vector Pos;
    CP_Vector Velocity;
    float radius;
    CP_Color color;
    int active;
    float lifetime;  // 총알의 생명 주기를 추적
} Bullet;

extern Bullet bullets[MAX_BULLETS];

void Initialize_Bullets();
void Bullet_Init(int index, CP_Vector position, CP_Vector velocity, float radius, CP_Color color);
void Bullet_Update();
void Bullet_Draw();
