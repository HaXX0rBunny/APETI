#include "enemy.h"
#include "Enemy.h"

extern int EnemyCount;

void Initialize_Enemy(struct Enemy* Enemy, float x, float y, float w, float h, CP_Color color, int removability, int exist)
{
	Enemy->Pos.x = x;
	Enemy->Pos.y = y;

	Enemy->w = w;
	Enemy->h = h;

	Enemy->color = color;

	Enemy->removability = removability;
	Enemy->exist = exist;

	if (exist) EnemyCount++;
}

int Enemy_MouseIn(struct Enemy* Enemy)
{
	float MouseX = CP_Input_GetMouseWorldX();
	float MouseY = CP_Input_GetMouseWorldY();

	float minX = Enemy->Pos.x;
	if (MouseX < minX)
		return 0;

	float minY = Enemy->Pos.y;
	if (MouseY < minY)
		return 0;

	float maxX = Enemy->Pos.x + Enemy->w;
	if (MouseX > maxX)
		return 0;

	float maxY = Enemy->Pos.y + Enemy->h;
	if (MouseY > maxY)
		return 0;

	return 1;
}