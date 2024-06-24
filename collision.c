#include "collision.h"

int CollisionIntersection_RectRect(float aX, float aY, float aW, float aH, float bX, float bY, float bW, float bH) {
    if (aX > bX + bW || aX + aW < bX || aY > bY + bH || aY + aH < bY) {
        return 0;  // �浹 ����
    }
    return 1;  // �浹 �߻�
}

int CollisionIntersection_RectMouse(float x, float y, float w, float h)
{
    float mouseX = CP_Input_GetMouseWorldX();
    float mouseY = CP_Input_GetMouseWorldY();

    if (mouseX < x || mouseX > x + w || mouseY < y || mouseY > y + h) {
        return 0;
    }
    return 1;
}

int checkCollision(const struct Platform* a, const struct Platform* b) {
    if (a->Pos.x < b->Pos.x + b->w &&
        a->Pos.x  + a->w > b->Pos.x &&
        a->Pos.y < b->Pos.y + b->h &&
        a->Pos.y + a->h > b->Pos.y) {
        return 1; // �浹 �߻�
    }
    return 0; // �浹 ����
}
int checkGroundCollision(const struct Platform* enemy, const struct Platform* platforms, int platformCount) {
    for (int i = 0; i < platformCount; ++i) {
        if (platforms[i].objecType == platform &&
            enemy->Pos.x < platforms[i].Pos.x + platforms[i].w &&
            enemy->Pos.x + enemy->w > platforms[i].Pos.x &&
            enemy->Pos.y + enemy->h == platforms[i].Pos.y&& platforms[i].exist) {
            return 1; // ���� �ٷ� �Ʒ��� �÷����� ����
        }
    }
    return 0; // ���� �Ʒ��� �÷����� ����
}

int checkNextPosition(const struct Platform* enemy, const struct Platform* platforms, int platformCount, int moveSpeed) {
    // ���� ���� ��ġ�� �̸� ����Ͽ� �� �ؿ� �÷����� �ִ��� Ȯ��
    struct Platform nextPosition = *enemy;
    if(moveSpeed>=0)
        nextPosition.Pos.x += moveSpeed+50;
    else
    {
        nextPosition.Pos.x += moveSpeed - 50;
    }
    return checkGroundCollision(&nextPosition, platforms, platformCount);
}
