#include "collision.h"

int CollisionIntersection_RectRect(float aX, float aY, float aW, float aH, float bX, float bY, float bW, float bH)
{
	if (aX > (bX + bW))
		return 0;

	if (bX > (aX + aW))
		return 0;

	if (aY > (bY + bH))
		return 0;

	if (bY > (aY + aH))
		return 0;

	return 1;
}
