#include "bullet.h"
#include "cprocessing.h"
#include "collision.h"  
#include "platform.h" 

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
    float subStep = 0.01f; // 더 촘촘한 업데이트 간격
    int steps = (int)(dt / subStep);
    for (int step = 0; step < steps; step++) {
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                CP_Vector newPos;
                newPos.x = bullets[i].Pos.x + bullets[i].Velocity.x * subStep;
                newPos.y = bullets[i].Pos.y + bullets[i].Velocity.y * subStep;
                int collided = 0;

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

                if (!collided) {
                    bullets[i].Pos = newPos;
                }

                // 생명 주기 감소
                bullets[i].lifetime -= subStep;
                if (bullets[i].lifetime <= 0) {
                    bullets[i].active = 0;  // 시간이 다 되면 비활성화
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
