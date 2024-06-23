#include "demon.h"
#include "player.h"  // Player 구조체와 관련 함수를 포함하기 위해 추가
#include "bullet.h"  // Bullet 구조체와 관련 함수를 포함하기 위해 추가
#include <math.h>
#include "game.h"
#include <stdio.h>
#define HIDDEN_YELLOW CP_Color_Create(255, 255, 0, 0)
#define YELLOW CP_Color_Create(255, 255, 0, 255)
#define RED CP_Color_Create(255, 0, 0, 255)
#define SUMMON_SPEED 0.4f
#define ATTACK_SPEED 1.3f
#define TWINKLE_SPEED 2.f
#define ATTACK_COOLDOWN 1.f
#define HIT_COOLDOWN 2.f  // 1초 쿨다운

struct Demon demon;
extern struct Player player;  // 외부에서 선언된 Player 사용
extern Bullet bullets[MAX_BULLETS];  // 외부에서 선언된 Bullets 배열 사용

int colList[BODY_ROW];

void Body_Init(struct Body* body, float x, float y, float desX, float desY, float w, float h, CP_Color color)
{
    body->pos.x = x;
    body->pos.y = y;

    body->start.x = x;
    body->start.y = y;

    body->end.x = desX;
    body->end.y = desY;

    body->w = w;
    body->h = h;

    body->color = color;

    int i = 0;
    for (i = 0; i < BODY_ROW; i++)
    {
        colList[i] = i;
    }
}

void Body_Draw(struct Body* body)
{
    CP_Settings_Fill(body->color);
    CP_Graphics_DrawRect(body->pos.x, body->pos.y, body->w, body->h);
}

int Body_Attack(struct Body* body)
{
    static float rot_counter = 0;
    rot_counter += CP_System_GetDt() * ATTACK_SPEED;

    if (fabsf(body->pos.x - body->end.x) > 0.5f)
    {
        // 충돌 감지 및 공격 로직 추가
        if (CollisionIntersection_RectRect(body->pos.x, body->pos.y, body->w, body->h, player.Pos.x, player.Pos.y, player.w, player.h)) {
            Player_ReduceHealth(demon.damage);  // 플레이어의 체력을 감소시킴
        }

        body->pos.x = CP_Math_LerpFloat(body->start.x, body->end.x, rot_counter);
        body->pos.y = CP_Math_LerpFloat(body->start.y, body->end.y, rot_counter);
        return 0;
    }
    else
    {
        rot_counter = 0;
        body->pos = body->end;
        body->end = body->start;
        body->start = body->pos;
        return 1;
    }
}

void Demon_Init(float x, float y, float desX, float desY, float w, float h, int health, int damage)
{
    demon.health = health;
    demon.damage = damage;
    demon.hitCooldown = 0;  // 피격 쿨다운 초기화

    int i = 0;
    int j = 0;

    Demon_Next_Eye();

    for (i = 0; i < BODY_ROW; i++)
    {
        for (j = 0; j < BODY_COL; j++)
        {
            Body_Init(&demon.body[i * BODY_COL + j], x + (w * j), y + (h * i), desX + (w * j), desY + (h * i), w, h, YELLOW);
        }
    }

    demon.isAttack = -1;
}

int Demon_Summon()
{
    static float rot_counter = 0;
    rot_counter += CP_System_GetDt() * SUMMON_SPEED;

    static int alpha;
    alpha = CP_Math_LerpInt(0, 255, rot_counter);

    int i = 0;

    for (i = 0; i < (BODY_COL * BODY_ROW); i++)
    {
        demon.body[i].color.a = (unsigned char)alpha;
    }

    if (alpha == 255)
    {
        rot_counter = 0;
        return 1;
    }

    return 0;
}

int Demon_Selete_Body(int* cnt) {
    int r = CP_Random_RangeInt(0, BODY_ROW - *cnt);

    int t = colList[r];
    colList[r] = colList[BODY_ROW - *cnt];
    colList[BODY_ROW - *cnt] = t;

    return t;
}

int Demon_Attack_Cooldown()
{
    static float t;
    t += CP_System_GetDt() * SUMMON_SPEED;
    if (t > ATTACK_COOLDOWN)
    {
        t = 0;
        return 1;
    }
    return 0;
}

int Demon_Attack()
{
    static int cnt = 1;
    static int j = -1;
    static int i = 0;

    if (j == -1 && cnt == BODY_ROW + 1) {
        if (i == BODY_COL - 1)
        {
            cnt = 1;
            j = -1;
            i = 0;
            return 1;
        }

        cnt = 1;
        i++;
    }

    if (j == -1)
    {
        j = Demon_Selete_Body(&cnt);
        cnt++;
    }

    if (Body_Attack(&demon.body[j * BODY_COL + i])) {
        j = -1;
    }

    return 0;
}

void Demon_Hit()
{
    // Demon의 눈이 반짝거릴 때 공격받으면 체력 감소
    if (demon.isAttack == 0 && demon.hitCooldown <= 0) {
        demon.health -= 1;  // 체력 감소
        printf("%d", demon.health);
        demon.hitCooldown = HIT_COOLDOWN;  // 쿨다운 설정
        if (demon.health <= 0) {
            Demon_Dead();  // 체력이 0 이하가 되면 Demon 제거
        }
    }
}

void Demon_Dead()
{
    demon.isAttack = -2;  // Demon을 비활성화하는 상태로 변경
    CP_Engine_SetNextGameStateForced(game_init, game_update, game_exit);

}

void Demon_Twinkle_Eye(int isOpen)
{
    static float rot_counter = 0;
    rot_counter += rot_counter >= 1.0f ? -1.f : CP_System_GetDt() * TWINKLE_SPEED;

    if (isOpen)
        demon.body[demon.eye * BODY_COL + (BODY_COL / 2)].color = CP_Color_Lerp(YELLOW, RED, rot_counter);
    else
        demon.body[demon.eye * BODY_COL + (BODY_COL / 2)].color = YELLOW;
}

void Demon_Next_Eye()
{
    demon.body[demon.eye * BODY_COL + (BODY_COL / 2)].color = YELLOW;
    demon.eye = CP_Random_RangeInt(1, BODY_ROW - 2);
}

void Demon_Draw()
{
    // Demon이 활성화된 경우에만 그리기
    if (demon.isAttack != -2) {
        int i = 0;

        for (i = 0; i < (BODY_COL * BODY_ROW); i++)
        {
            Body_Draw(&demon.body[i]);
        }
    }
}

void Demon_Update()
{
    // Demon이 활성화된 경우에만 업데이트
    if (demon.isAttack != -2) {
        float dt = CP_System_GetDt();

        // 피격 쿨다운 업데이트
        if (demon.hitCooldown > 0) {
            demon.hitCooldown -= dt;
        }

        switch (demon.isAttack)
        {
        case -1:
            Demon_Twinkle_Eye(0);
            if (Demon_Summon())
                demon.isAttack = 0;
            break;
        case 0:
            Demon_Twinkle_Eye(1);
            if (Demon_Attack_Cooldown())
            {
                demon.isAttack = 1;
                Demon_Next_Eye();
            }
            break;
        case 1:
            Demon_Twinkle_Eye(0);
            if (Demon_Attack())
                demon.isAttack = 0;
            break;
        }
    }
}
