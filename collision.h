#pragma once

#include "cprocessing.h"
#include "platform.h"

int CollisionIntersection_RectRect(float aX, float aY, float aW, float aH, float bX, float bY, float bW, float bH);
int checkCollision(const struct Platform* a, const struct Platform* b); 
int checkGroundCollision(const struct Platform* enemy, const struct Platform* platforms, int platformCount);
int checkNextPosition(const struct Platform* enemy, const struct Platform* platforms, int platformCnt, int moveSpeed);