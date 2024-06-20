#pragma once
#include "map.h"
#include "cprocessing.h"

#define MAX_BOMBS 50

typedef struct Bomb {
    CP_Vector Pos;
    CP_Vector Velocity;
    float radius;
    CP_Color color;
    int active;       // 폭탄의 활성 상태
    int exploded;     // 폭탄이 터졌는지 여부
    float explodeTimer;  // 폭발까지 남은 시간
} Bomb;

extern Bomb bombs[MAX_BOMBS];

void Initialize_Bombs();
void Bomb_Init(int index, CP_Vector position, CP_Vector velocity, float radius, CP_Color color);
void Bomb_Update();
void Bomb_Draw();