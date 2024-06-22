#include "platform.h"

extern int platformCount;

void Initialize_Platform(struct Platform* platform, float x, float y, float w, float h, CP_Color color, int removability, int exist, int objecType, int hitcount)
{
	platform->Pos.x = x;
	platform->Pos.y = y;

	platform->w = w;
	platform->h = h;

	platform->color = color;

	platform->removability = removability;
	platform->exist = exist;
	platform->hitcount = hitcount;
	platform->objecType = objecType;
	platform->velocity = CP_Vector_Set(0, 0);
	if (exist) platformCount++;
}

int Platform_MouseIn(struct Platform* platform)
{
	float MouseX = CP_Input_GetMouseWorldX();
	float MouseY = CP_Input_GetMouseWorldY();

	float minX = platform->Pos.x;
	if (MouseX < minX)
		return 0;

	float minY = platform->Pos.y;
	if (MouseY < minY)
		return 0;

	float maxX = platform->Pos.x + platform->w;
	if (MouseX > maxX)
		return 0;

	float maxY = platform->Pos.y + platform->h;
	if (MouseY > maxY)
		return 0;

	return 1;
}