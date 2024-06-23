#include "bomb.h"
#include "platform.h"
#include "collision.h"
#include "sanic.h"  // Sanic 구조체를 포함하기 위해 추가
#include "stdio.h"

extern struct Platform platformList[MAX_PLATFORM_LIST_SIZE];  // 플랫폼 배열
extern struct Sanic sanic;  // 외부에서 선언된 Sanic 사용

Bomb bombs[MAX_BOMBS];

void Initialize_Bombs() {
    for (int i = 0; i < MAX_BOMBS; i++) {
        bombs[i].active = 0;  // 모든 폭탄을 비활성화 상태로 초기화
    }
}

void Bomb_Init(int index, CP_Vector position, CP_Vector velocity, float radius, CP_Color color) {
    if (index < 0 || index >= MAX_BOMBS) return;
    bombs[index].Pos = position;
    bombs[index].Velocity = velocity;
    bombs[index].radius = radius;
    bombs[index].color = color;
    bombs[index].active = 1;
    bombs[index].exploded = 0;
    bombs[index].explodeTimer = 0;
    bombs[index].activationTimer = 2.0f;  // 3초 후에 자동으로 터짐
}

void Bomb_Update() {
    float dt = CP_System_GetDt();
    float gravity = 500.1f;  // 중력 가속도
    for (int i = 0; i < MAX_BOMBS; i++) {
        Bomb* bomb = &bombs[i];
        if (bomb->active) {
            if (!bomb->exploded) {
                bomb->Velocity.y += gravity * dt;  // 중력 적용
                bomb->Pos.x += bomb->Velocity.x * dt;
                bomb->Pos.y += bomb->Velocity.y * dt;

                // 플랫폼과 충돌 검사
                for (int j = 0; j < MAX_PLATFORM_LIST_SIZE; j++) {
                    if (platformList[j].exist && CollisionIntersection_RectRect(bomb->Pos.x - bomb->radius, bomb->Pos.y - bomb->radius, bomb->radius * 2, bomb->radius * 2, platformList[j].Pos.x, platformList[j].Pos.y, platformList[j].w, platformList[j].h)) {
                        bomb->exploded = 1;
                        bomb->explodeTimer = 0.7f;  // 0.7초 동안 폭발 효과

                        if (platformList[j].removability == 1)
                            Remove_Platform(&platformList[j]);
                        break;
                    }
                }

                // Sanic과 충돌 검사
                if (sanic.active && CollisionIntersection_RectRect(bomb->Pos.x - bomb->radius, bomb->Pos.y - bomb->radius, bomb->radius * 2, bomb->radius * 2, sanic.pos.x, sanic.pos.y, sanic.w, sanic.h)) {
                    bomb->exploded = 1;
                    bomb->explodeTimer = 0.7f;  // 0.7초 동안 폭발 효과
                    sanic.state = 1;  // Sanic 상태 변경
                }

                // 자동 폭발 타이머 업데이트
                bomb->activationTimer -= dt;
                if (bomb->activationTimer <= 0) {
                    bomb->exploded = 1;
                    bomb->explodeTimer = 0.7f;  // 0.7초 동안 폭발 효과
                }
            }
            else {
                bomb->explodeTimer -= dt;
                if (bomb->explodeTimer <= 0) {
                    bomb->active = 0;  // 폭탄 비활성화
                }
            }
        }
    }
}

void Bomb_Draw() {
    for (int i = 0; i < MAX_BOMBS; i++) {
        Bomb* bomb = &bombs[i];
        if (bomb->active) {
            CP_Settings_Fill(bomb->color);
            CP_Graphics_DrawCircle(bomb->Pos.x, bomb->Pos.y, bomb->radius);

            // 폭발 직전의 이펙트 표시
            if (bomb->exploded && bomb->explodeTimer > 0) {
                CP_Settings_Fill(CP_Color_Create(255, 69, 0, 255));  // 오렌지색 폭발 효과
                CP_Graphics_DrawCircle(bomb->Pos.x, bomb->Pos.y, bomb->radius * 5.0f);
            }
        }
    }
}
