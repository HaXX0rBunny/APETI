#include "platform.h"

void Initialize_Platform(struct Platform* platform, float x, float y, float w, float h, CP_Color color, int removability, int visibility)
{
	platform->Pos.x = x;
	platform->Pos.y = y;

	platform->w = w;
	platform->h = h;

	platform->color = color;

	platform->removability = removability;
	platform->visibility = visibility;
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