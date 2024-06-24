#include "enemyAi.h"
#include "platform.h"
#include "collision.h" // ���̳� ���������� �����ϱ� ���� �ʿ��� ��� ����

extern struct Platform platformList[MAX_PLATFORM_LIST_SIZE];
extern int platformCount; // �÷��� �迭�� ũ��

void updateEnemies() {
    for (int i = 0; i < platformCount; ++i) {
        if (platformList[i].objecType == enemy) {
            struct Platform* Enemy = &platformList[i];

            // �̵� �� �� �ؿ� �÷����� �ִ��� Ȯ��

            CP_Vector originalPos = Enemy->Pos;
            Enemy->Pos.x += Enemy->moveSpeed;

            if (!checkNextPosition(Enemy, platformList, platformCount, Enemy->moveSpeed)) {
                Enemy->Pos = originalPos; // ���� ��ġ�� �ǵ���
                Enemy->moveSpeed = -Enemy->moveSpeed; // ���� ��ȯ
            }

            // �� ����
            int isColliding = 0;
            for (int j = 0; j < platformCount; ++j) {
                if (i != j && platformList[j].objecType != enemy && checkCollision(Enemy, &platformList[j])) {
                    isColliding = 1;
                    break;
                }
            }

            // ���� ������ ���� ��ȯ
            if (isColliding) {
                Enemy->Pos = originalPos; // ���� ��ġ�� �ǵ���
                Enemy->moveSpeed = -Enemy->moveSpeed; // ���� ��ȯ
                Enemy->Pos.x += Enemy->moveSpeed;
            }
        }
    }
}
