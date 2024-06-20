#include "bomb.h"
#include "platform.h"
#include "collision.h"

extern struct Platform platformList[MAX_PLATFORM_LIST_SIZE];  // �÷��� �迭

Bomb bombs[MAX_BOMBS];

void Initialize_Bombs() {
    for (int i = 0; i < MAX_BOMBS; i++) {
        bombs[i].active = 0;  // ��� ��ź�� ��Ȱ��ȭ ���·� �ʱ�ȭ
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
}

void Bomb_Update() {
    float dt = CP_System_GetDt();
    float gravity = 500.1f;  // �߷� ���ӵ�
    for (int i = 0; i < MAX_BOMBS; i++) {
        Bomb* bomb = &bombs[i];
        if (bomb->active) {
            if (!bomb->exploded) {
                bomb->Velocity.y += gravity * dt;  // �߷� ����
                bomb->Pos.x += bomb->Velocity.x * dt;
                bomb->Pos.y += bomb->Velocity.y * dt;

                // �÷����� �浹 �˻�
                for (int j = 0; j < MAX_PLATFORM_LIST_SIZE; j++) {
                    if (platformList[j].exist && CollisionIntersection_RectRect(
                        bomb->Pos.x - bomb->radius, bomb->Pos.y - bomb->radius,
                        bomb->radius * 2, bomb->radius * 2,
                        platformList[j].Pos.x, platformList[j].Pos.y,
                        platformList[j].w, platformList[j].h)) {
                        bomb->exploded = 1;
                        bomb->explodeTimer = 0.5f;  // 1�� �Ŀ� ����
                        break;
                    }
                }
            }
            else {
                bomb->explodeTimer -= dt;
                if (bomb->explodeTimer <= 0) {
                    bomb->active = 0;  // ��ź ��Ȱ��ȭ
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

            // ���� ������ ����Ʈ ǥ��
            if (bomb->exploded && bomb->explodeTimer > 0) {
                CP_Settings_Fill(CP_Color_Create(255, 69, 0, 255));  // �������� ���� ȿ��
                CP_Graphics_DrawCircle(bomb->Pos.x, bomb->Pos.y, bomb->radius * 5.0f);
            }
        }
    }
}
