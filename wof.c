#include "wof.h"
#include "player.h"
#include "bullet.h"
#include "collision.h"
#include "bomb.h"
#include "game.h"
#include "gameClear.h"
#define EYE_PADDING 30

#define YELLOW CP_Color_Create(240, 240, 0, 255)
#define GRAY CP_Color_Create(110, 110, 110, 255)
#define MAX_TIMER 1.f
#define HIT_COOLDOWN 1.f
#define WALL_SPEED 100.f
#define BULLET_SPEED 800.f
#define BULLET_RADIUS 40.f

struct Wof wof;
extern struct Player player;

int eyeList[3];
float open_timer, close_timer;

void WofEye_Init(struct WofEye* wofEye, float x, float y, float w, float h, int damage)
{
    wofEye->pos.x = x;
    wofEye->pos.y = y;
    wofEye->w = w;
    wofEye->h = h;
    wofEye->damage = damage;
    wofEye->isOpen = 0;
    wofEye->eyeCover_color = GRAY;
    wofEye->color = YELLOW;

    open_timer = 0;
    close_timer = 0;
}

void WofEye_Attack(struct WofEye* wofEye)
{
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!wof.bullets[i].active) {
            wof.bullets[i].Pos = wofEye->pos;
            CP_Vector direction = CP_Vector_Subtract(player.Pos, wofEye->pos);
            wof.bullets[i].Velocity = CP_Vector_Scale(CP_Vector_Normalize(direction), BULLET_SPEED);
            wof.bullets[i].radius = BULLET_RADIUS;
            wof.bullets[i].active = 1;
            wof.bullets[i].color = YELLOW;
            break;
        }
    }
}

int WofEye_Hit(struct WofEye* wofEye)
{
    return 0;
}

int WofEye_Open(struct WofEye* wofEye)
{
    static float eyeH = 0;

    open_timer += CP_System_GetDt();
    eyeH = CP_Math_LerpFloat(wofEye->h / 2.f, 0, open_timer);

    CP_Settings_Fill(GRAY);
    CP_Graphics_DrawRect(wofEye->pos.x, wofEye->pos.y, wofEye->w, eyeH);
    CP_Graphics_DrawRect(wofEye->pos.x, wofEye->pos.y + wofEye->h - eyeH, wofEye->w, eyeH);

    if (open_timer > 0.99f)
    {
        open_timer = 0;
        eyeH = wofEye->h / 2.f;
        return 1;
    }
    return 0;
}

int WofEye_Close(struct WofEye* wofEye)
{
    close_timer += CP_System_GetDt();
    static float eyeH = 0;
    eyeH = CP_Math_LerpFloat(0, wofEye->h / 2.f, close_timer);

    CP_Settings_Fill(GRAY);
    CP_Graphics_DrawRect(wofEye->pos.x, wofEye->pos.y, wofEye->w, eyeH);
    CP_Graphics_DrawRect(wofEye->pos.x, wofEye->pos.y + wofEye->h - eyeH, wofEye->w, eyeH);

    if (close_timer > 0.99f)
    {
        close_timer = 0;
        eyeH = 0;
        return 1;
    }
    return 0;
}
void WofEye_Draw(struct WofEye* wofEye)
{
    // 눈 색상 설정
    CP_Settings_Fill(wofEye->color);
    // 눈 그리기
    CP_Graphics_DrawRect(wofEye->pos.x, wofEye->pos.y, wofEye->w, wofEye->h);

    // 눈이 열리지 않았을 때 덮개 그리기
    if (!wofEye->isOpen)
    {
        // 눈 덮개 색상 설정
        CP_Settings_Fill(GRAY);  // 회색으로 설정
        CP_Graphics_DrawRect(wofEye->pos.x, wofEye->pos.y, wofEye->w, wofEye->h / 2.f);
        CP_Graphics_DrawRect(wofEye->pos.x, wofEye->pos.y + (wofEye->h / 2.f), wofEye->w, wofEye->h / 2.f);
    }
}

void Wall_Init(struct Wall* wall, float x, float y, float w, float h)
{
    wall->pos.x = x;
    wall->pos.y = y;
    wall->w = w;
    wall->h = h;
    wall->active = 1;
    wall->color = CP_Color_Create(25, 255, 255, 150);
}

void Wof_Init(float x, float y, float w, float h, int health, int damage)
{
    wof.pos.x = x;
    wof.pos.y = y;
    wof.w = w;
    wof.h = h;
    wof.health = health;
    wof.hitCooldown = 0;
    wof.wallCounter = 0;
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        WofEye_Init(&wof.eye[i], x - EYE_PADDING, y + (h / 7.f * (2 * (i + 1) - 1)), EYE_PADDING, (h / 7.f), damage);
    }
    for (i = 0; i < MAX_WALLS; i++)
    {
        wof.walls[i].active = 0;
    }
    for (i = 0; i < MAX_BULLETS; i++)
    {
        wof.bullets[i].active = 0;
    }
    wof.state = 0;
    wof.color = GRAY;
}

void Wof_Create_Wall()
{
    for (int i = 0; i < MAX_WALLS; i++) {
        if (!wof.walls[i].active) {
            Wall_Init(&wof.walls[i], wof.pos.x - 200, wof.pos.y, 200, wof.h);
            break;
        }
    }
}

void Wof_Hit()
{
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        if (wof.eye[i].isOpen)
        {
            if (WofEye_Hit(&wof.eye[i]))
            {
                wof.health--;
                wof.wallCounter++;
                if (wof.wallCounter >= 3) {
                    Wof_Create_Wall();
                    wof.wallCounter = 0;
                }
            }
        }
    }
}

void Wof_Draw_Walls()
{
    for (int i = 0; i < MAX_WALLS; i++) {
        if (wof.walls[i].active) {
            CP_Settings_Fill(wof.walls[i].color);
            CP_Graphics_DrawRect(wof.walls[i].pos.x, wof.walls[i].pos.y, wof.walls[i].w, wof.walls[i].h);
        }
    }
}

void Wof_Draw_Bullets()
{
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (wof.bullets[i].active) {
            CP_Settings_Fill(wof.bullets[i].color);
            CP_Graphics_DrawCircle(wof.bullets[i].Pos.x, wof.bullets[i].Pos.y, wof.bullets[i].radius);
        }
    }
}

void Wof_Update_Bullets(float dt)
{
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (wof.bullets[i].active) {
            wof.bullets[i].Pos = CP_Vector_Add(wof.bullets[i].Pos, CP_Vector_Scale(wof.bullets[i].Velocity, dt));

            // 벽과 충돌하는지 확인
            for (int j = 0; j < MAX_WALLS; j++) {
                if (wof.walls[j].active && CollisionIntersection_RectRect(
                    wof.bullets[i].Pos.x - wof.bullets[i].radius, wof.bullets[i].Pos.y - wof.bullets[i].radius,
                    wof.bullets[i].radius * 2, wof.bullets[i].radius * 2,
                    wof.walls[j].pos.x, wof.walls[j].pos.y, wof.walls[j].w, wof.walls[j].h)) {
                    wof.bullets[i].active = 0;
                }
            }

            // 플레이어와 충돌하는지 확인
            if (CollisionIntersection_RectRect(
                wof.bullets[i].Pos.x - wof.bullets[i].radius, wof.bullets[i].Pos.y - wof.bullets[i].radius,
                wof.bullets[i].radius * 2, wof.bullets[i].radius * 2,
                player.Pos.x, player.Pos.y, player.w, player.h)) {
                Player_ReduceHealth(3);
                wof.bullets[i].active = 0;
            }

            // 화면 밖으로 나가면 비활성화
            if (wof.bullets[i].Pos.x < 0 || wof.bullets[i].Pos.x > CP_System_GetWindowWidth() +150||
                wof.bullets[i].Pos.y < 0 || wof.bullets[i].Pos.y > CP_System_GetWindowHeight()+150) {
                wof.bullets[i].active = 0;
            }
        }
    }
}

void Wof_Update_Walls(float dt)
{
    for (int i = 0; i < MAX_WALLS; i++) {
        if (wof.walls[i].active) {
            wof.walls[i].pos.x -= WALL_SPEED * dt;

            // 벽이 플레이어와 충돌하는지 확인
            if (CollisionIntersection_RectRect(
                wof.walls[i].pos.x, wof.walls[i].pos.y, wof.walls[i].w, wof.walls[i].h,
                player.Pos.x, player.Pos.y, player.w, player.h)) {
                Player_ReduceHealth(2);

                // 플레이어가 벽을 따라 밀리도록 위치 조정
                player.Pos.x -= WALL_SPEED * dt;
            }

            // 벽이 총알과 충돌하는지 확인
            for (int j = 0; j < MAX_BULLETS; j++) {
                if (bullets[j].active && CollisionIntersection_RectRect(
                    wof.walls[i].pos.x, wof.walls[i].pos.y, wof.walls[i].w, wof.walls[i].h,
                    bullets[j].Pos.x - bullets[j].radius, bullets[j].Pos.y - bullets[j].radius,
                    bullets[j].radius * 2, bullets[j].radius * 2)) {
                    bullets[j].active = 0;
                }
            }

            // 벽이 폭탄과 충돌하는지 확인
            for (int k = 0; k < MAX_BOMBS; k++) {
                if (bombs[k].active && CollisionIntersection_RectRect(
                    wof.walls[i].pos.x, wof.walls[i].pos.y, wof.walls[i].w, wof.walls[i].h,
                    bombs[k].Pos.x - bombs[k].radius, bombs[k].Pos.y - bombs[k].radius,
                    bombs[k].radius * 2, bombs[k].radius * 2)) {
                    wof.walls[i].active = 0;
                }
            }

            // 벽이 화면 밖으로 나가면 비활성화
            if (wof.walls[i].pos.x + wof.walls[i].w < 0) {
                wof.walls[i].active = 0;
            }
        }
    }
}

int Wof_Timer()
{
    static float timer = 0;
    float t = CP_System_GetDt();

    timer += t;
    if (timer > MAX_TIMER)
    {
        timer = 0;
        return 1;
    }

    return 0;
}

void Wof_Draw()
{
    if (wof.state != -1) {
        int i = 0;
        for (i = 0; i < 3; i++)
        {
            WofEye_Draw(&wof.eye[i]);
        }

        CP_Settings_Fill(wof.color);
        CP_Graphics_DrawRect(wof.pos.x, wof.pos.y, wof.w, wof.h);
    }

    Wof_Draw_Walls();
    Wof_Draw_Bullets();
}
void Wof_Dead() {
    wof.state = -1;
    CP_Engine_SetNextGameStateForced(GameClear_init, GameClear_update, GameClear_exit);
}

void Wof_Update()
{
    if (wof.state != -1) {
        float dt = CP_System_GetDt();

        if (wof.hitCooldown > 0) {
            wof.hitCooldown -= dt;
        }

        Wof_Update_Walls(dt);
        Wof_Update_Bullets(dt);

        static int r = 0;

        switch (wof.state)
        {
        case 0:
            r = CP_Random_RangeInt(0, 2);
            wof.eye[r].isOpen = 1;
            wof.state = 1;
            break;
        case 1:
            if (WofEye_Open(&wof.eye[r]))
            {
                wof.state = 2;
            }
            break;
        case 2:
            WofEye_Attack(&wof.eye[r]);
            if (Wof_Timer())
            {
                wof.state = 3;
            }
            break;
        case 3:
            if (WofEye_Close(&wof.eye[r]))
            {
                wof.eye[r].isOpen = 0;
                wof.state = 0;
            }
            break;
        }
    }
}

void Wof_BulletHit()
{
    if (wof.hitCooldown <= 0) {
        int i;
        for (i = 0; i < 3; i++)
        {
            if (wof.eye[i].isOpen)
            {
                wof.health--;
                wof.wallCounter++;
                if (wof.wallCounter >= 3) {
                    Wof_Create_Wall();
                    wof.wallCounter = 0;
                }
                wof.hitCooldown = HIT_COOLDOWN;
                if (wof.health <= 0)
                {
                    
                    Wof_Dead();
                }
            }
        }
    }
}
