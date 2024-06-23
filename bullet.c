#include "bullet.h"
#include "cprocessing.h"
#include "collision.h"  
#include "platform.h" 
#include "sanic.h"
#include "demon.h" 
#include "wof.h"  // WOF ����ü�� ���� �Լ��� �����ϱ� ���� �߰�
#include <stdio.h>
extern struct Sanic sanic;
extern struct Demon demon;
Bullet bullets[MAX_BULLETS];
extern struct Platform platformList[MAX_PLATFORM_LIST_SIZE];  // �÷��� �迭


extern struct Wof wof;  // �ܺο��� ����� WOF ���
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
    float subStep = dt / 3.0f;
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            for (int step = 0; step < 3; step++) {
                CP_Vector newPos;
                newPos.x = bullets[i].Pos.x + bullets[i].Velocity.x * subStep;
                newPos.y = bullets[i].Pos.y + bullets[i].Velocity.y * subStep;
                int collided = 0;

                // �÷����� �浹 �˻�
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

                // Sanic�� �浹 �˻�
                if (sanic.active && CollisionIntersection_RectRect(newPos.x - bullets[i].radius, newPos.y - bullets[i].radius, bullets[i].radius * 2, bullets[i].radius * 2, sanic.pos.x, sanic.pos.y, sanic.w, sanic.h)) {
                    if (sanic.hitCooldown <= 0) {  // �ǰ� ��ٿ� Ȯ��
                        bullets[i].active = 0;
                        sanic.health -= 1;  // Sanic�� ü���� 1 ����
                        sanic.hitCooldown = 0.5f;  // �ǰ� ��ٿ� ����
                        printf("%d", sanic.health);
                        if (sanic.health <= 0) {
                            sanic.active = 0;  // Sanic ��Ȱ��ȭ
                        }
                    }
                    collided = 1;
                }
                // Demon�� �浹 �˻�
                if (demon.isAttack != -2 && CollisionIntersection_RectRect(newPos.x - bullets[i].radius, newPos.y - bullets[i].radius, bullets[i].radius * 2, bullets[i].radius * 2, demon.body[demon.eye * BODY_COL + (BODY_COL / 2)].pos.x, demon.body[demon.eye * BODY_COL + (BODY_COL / 2)].pos.y, demon.body[demon.eye * BODY_COL + (BODY_COL / 2)].w, demon.body[demon.eye * BODY_COL + (BODY_COL / 2)].h)) {
                    bullets[i].active = 0;
                    Demon_Hit();  // Demon�� ü���� ���ҽ�Ű�� �Լ� ȣ��
                    collided = 1;
                }

                for (int k = 0; k < 3; k++) {
                    if (wof.eye[k].isOpen && CollisionIntersection_RectRect(newPos.x - bullets[i].radius, newPos.y - bullets[i].radius, bullets[i].radius * 2, bullets[i].radius * 2, wof.eye[k].pos.x, wof.eye[k].pos.y, wof.eye[k].w, wof.eye[k].h)) {
                        bullets[i].active = 0;
                        Wof_BulletHit();  // WOF�� ü���� ���ҽ�Ű�� �Լ� ȣ��
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
