#include "bullet.h"
#include "cprocessing.h"
#include "collision.h"  // �浹 �˻� �Լ��� ���Ե� ��� ����
#include "platform.h" 
Bullet bullets[MAX_BULLETS];

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
    bullets[index].lifetime = 3.0;  // 3�ʰ� Ȱ��ȭ
}

void Bullet_Update() {
    float dt = CP_System_GetDt();
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].Pos.x += bullets[i].Velocity.x * dt;
            bullets[i].Pos.y += bullets[i].Velocity.y * dt;

            // ���� �ֱ� ����
            bullets[i].lifetime -= dt;
            if (bullets[i].lifetime <= 0) {
                bullets[i].active = 0;  // �ð��� �� �Ǹ� ��Ȱ��ȭ
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
