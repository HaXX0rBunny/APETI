#pragma once
#include "map.h"
#include "cprocessing.h"

#define MAX_BOMBS 50

typedef struct Bomb {
    CP_Vector Pos;
    CP_Vector Velocity;
    float radius;
    CP_Color color;
    int active;       // ��ź�� Ȱ�� ����
    int exploded;     // ��ź�� �������� ����
    float explodeTimer;  // ���߱��� ���� �ð�
} Bomb;

extern Bomb bombs[MAX_BOMBS];

void Initialize_Bombs();
void Bomb_Init(int index, CP_Vector position, CP_Vector velocity, float radius, CP_Color color);
void Bomb_Update();
void Bomb_Draw();