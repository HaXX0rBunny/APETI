#include "enemyAi.h"
#include "platform.h"
#include "collision.h" // 벽이나 낭떠러지를 감지하기 위해 필요한 헤더 파일

extern struct Platform platformList[MAX_PLATFORM_LIST_SIZE];
extern int platformCount; // 플랫폼 배열의 크기

void updateEnemies() {
    for (int i = 0; i < platformCount; ++i) {
        if (platformList[i].objecType == enemy) {
            struct Platform* Enemy = &platformList[i];

            // 이동 후 발 밑에 플랫폼이 있는지 확인

            CP_Vector originalPos = Enemy->Pos;
            Enemy->Pos.x += Enemy->moveSpeed;

            if (!checkNextPosition(Enemy, platformList, platformCount, Enemy->moveSpeed)) {
                Enemy->Pos = originalPos; // 원래 위치로 되돌림
                Enemy->moveSpeed = -Enemy->moveSpeed; // 방향 전환
            }

            // 벽 감지
            int isColliding = 0;
            for (int j = 0; j < platformCount; ++j) {
                if (i != j && platformList[j].objecType != enemy && checkCollision(Enemy, &platformList[j])) {
                    isColliding = 1;
                    break;
                }
            }

            // 벽을 만나면 방향 전환
            if (isColliding) {
                Enemy->Pos = originalPos; // 원래 위치로 되돌림
                Enemy->moveSpeed = -Enemy->moveSpeed; // 방향 전환
                Enemy->Pos.x += Enemy->moveSpeed;
            }
        }
    }
}
