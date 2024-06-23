#include "bullet.h"
#include "cprocessing.h"
#include "collision.h"  
#include "platform.h" 
#include "sanic.h"
#include <stdio.h>
extern struct Sanic sanic;

Bullet bullets[MAX_BULLETS];
extern struct Platform platformList[MAX_PLATFORM_LIST_SIZE];  // 플랫폼 배열

void Initialize_Bullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = 0;
    }
}

void Bullet_Init(int index, CP_Vector position, CP_Vector velocity, float radius, CP_Color color) {
    if (index < 0 || index >= MAX_BULLETS) return;
    bullets[index].Pos = position;
    bullets[index].Velocity = velocity;
    bullets[index].radius = radius;
    bullets[index].color = color;
    bullets[index].active = 1;
    bullets[index].lifetime = 3.0;  // 3초간 활성화
}

void Bullet_Update() {
    float dt = CP_System_GetDt();
    float subStep = dt / 3.0f;
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            for (int step = 0; step < 3; step++) {
                CP_Vector newPos;
                newPos.x = bullets[i].Pos.x + bullets[i].Velocity.x * subStep;
                newPos.y = bullets[i].Pos.y + bullets[i].Velocity.y * subStep;
                int collided = 0;

                // 플랫폼과 충돌 검사
                for (int j = 0; j < MAX_PLATFORM_LIST_SIZE; j++) {
                    if (platformList[j].exist && CollisionIntersection_RectRect(newPos.x - bullets[i].radius, newPos.y - bullets[i].radius, bullets[i].radius * 2, bullets[i].radius * 2, platformList[j].Pos.x, platformList[j].Pos.y, platformList[j].w, platformList[j].h)) {
                        bullets[i].active = 0;

                        if (platformList[j].objecType == 1)
                            platformList[j].hitcount++;

                        if (platformList[j].hitcount >= 3)
                            Remove_Platform(&platformList[j]);
                        collided = 1;
                        break;
                    }
                }

                // Sanic과 충돌 검사
                if (sanic.active && CollisionIntersection_RectRect(newPos.x - bullets[i].radius, newPos.y - bullets[i].radius, bullets[i].radius * 2, bullets[i].radius * 2, sanic.pos.x, sanic.pos.y, sanic.w, sanic.h)) {
                    if (sanic.hitCooldown <= 0) {  // 피격 쿨다운 확인
                        bullets[i].active = 0;
                        sanic.health -= 1;  // Sanic의 체력을 1 감소
                        sanic.hitCooldown = 0.5f;  // 피격 쿨다운 설정
                        printf("%d", sanic.health);
                        if (sanic.health <= 0) {
                            sanic.active = 0;  // Sanic 비활성화
                        }
                    }
                    collided = 1;
                }

                if (!collided) {
                    bullets[i].Pos = newPos;
                }

                bullets[i].lifetime -= subStep;
                if (bullets[i].lifetime <= 0) {
                    bullets[i].active = 0;
                }
            }
        }
    }
}

void Bullet_Draw() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            CP_Settings_Fill(bullets[i].color);
            CP_Graphics_DrawCircle(bullets[i].Pos.x, bullets[i].Pos.y, bullets[i].radius);
        }
    }
}
