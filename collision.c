#include "collision.h"

int CollisionIntersection_RectRect(float aX, float aY, float aW, float aH, float bX, float bY, float bW, float bH) {
    if (aX > bX + bW || aX + aW < bX || aY > bY + bH || aY + aH < bY) {
        return 0;  // �浹 ����
    }
    return 1;  // �浹 �߻�
}
