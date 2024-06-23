#pragma once

#include "cprocessing.h"
#include "bullet.h"  // Bullet 구조체와 관련 함수를 포함

#define MAX_WALLS 10

typedef struct WofEye
{
    CP_Vector pos;
    float w, h;
    int damage;
    int isOpen;
    CP_Color color;
    CP_Color eyeCover_color;
} WofEye;

typedef struct Wall
{
    CP_Vector pos;
    float w, h;
    int active;
    CP_Color color;
} Wall;

typedef struct Wof
{
    CP_Vector pos;
    float w, h;
    int health;
    float hitCooldown;
    int wallCounter;
    int state;
    CP_Color color;
    WofEye eye[3];
    Wall walls[MAX_WALLS];
    Bullet bullets[MAX_BULLETS];
} Wof;

extern Wof wof;
void Wof_Dead();
void Wof_Init(float x, float y, float w, float h, int health, int damage);
void Wof_Create_Wall();
void Wof_Hit();
void Wof_Draw();
void Wof_Update();
void Wof_BulletHit();
void WofEye_Init(WofEye* wofEye, float x, float y, float w, float h, int damage);
void WofEye_Attack(WofEye* wofEye);
int WofEye_Hit(WofEye* wofEye);
int WofEye_Open(WofEye* wofEye);
int WofEye_Close(WofEye* wofEye);
void WofEye_Draw(WofEye* wofEye);
void Wall_Init(Wall* wall, float x, float y, float w, float h);
void Wof_Draw_Walls();
void Wof_Update_Walls(float dt);
int Wof_Timer();
