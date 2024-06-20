#include "bullet.h"
#include "cprocessing.h"
#include "collision.h"  // 충돌 검사 함수가 포함된 헤더 파일
#include "platform.h" 
#include "stdio.h"
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
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].Pos.x += bullets[i].Velocity.x * dt;
            bullets[i].Pos.y += bullets[i].Velocity.y * dt;


            for (int j = 0; j < MAX_PLATFORM_LIST_SIZE; j++) {
                if (platformList[j].exist && CollisionIntersection_RectRect(bullets->Pos.x - bullets->radius*2, bullets->Pos.y - bullets->radius*2, bullets->radius * 2, bullets->radius * 2, platformList[j].Pos.x, platformList[j].Pos.y, platformList[j].w, platformList[j].h)) {
                    bullets[i].active = 0;   
                    printf(" % d", platformList[j].objecType);
                    if(platformList[j].objecType == 1)
                        platformList[j].hitcount++;
                    printf(" % d", platformList[j].hitcount);
                   
                    if (platformList[j].hitcount >= 3) 
                        Remove_Platform(&platformList[j]);
                    break;
                  
                }
            }
            // 생명 주기 감소
            bullets[i].lifetime -= dt;
            if (bullets[i].lifetime <= 0) {
                bullets[i].active = 0;  // 시간이 다 되면 비활성화
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
