#include "bullet.h"
#include "cprocessing.h"
#include "collision.h"  
#include "platform.h" 
#include "sanic.h"
#include "demon.h" 
#include "wof.h"  // WOF 구조체와 관련 함수를 포함하기 위해 추가
#include <stdio.h>
extern struct Sanic sanic;
extern struct Demon demon;
Bullet bullets[MAX_BULLETS];
extern struct Platform platformList[MAX_PLATFORM_LIST_SIZE];  // 플랫폼 배열


extern struct Wof wof;  // 외부에서 선언된 WOF 사용
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
                // Demon과 충돌 검사
                if (demon.isAttack != -2 && CollisionIntersection_RectRect(newPos.x - bullets[i].radius, newPos.y - bullets[i].radius, bullets[i].radius * 2, bullets[i].radius * 2, demon.body[demon.eye * BODY_COL + (BODY_COL / 2)].pos.x, demon.body[demon.eye * BODY_COL + (BODY_COL / 2)].pos.y, demon.body[demon.eye * BODY_COL + (BODY_COL / 2)].w, demon.body[demon.eye * BODY_COL + (BODY_COL / 2)].h)) {
                    bullets[i].active = 0;
                    Demon_Hit();  // Demon의 체력을 감소시키는 함수 호출
                    collided = 1;
                }

                for (int k = 0; k < 3; k++) {
                    if (wof.eye[k].isOpen && CollisionIntersection_RectRect(newPos.x - bullets[i].radius, newPos.y - bullets[i].radius, bullets[i].radius * 2, bullets[i].radius * 2, wof.eye[k].pos.x, wof.eye[k].pos.y, wof.eye[k].w, wof.eye[k].h)) {
                        bullets[i].active = 0;
                        Wof_BulletHit();  // WOF의 체력을 감소시키는 함수 호출
                        collided = 1;
                        break;
                    }
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
