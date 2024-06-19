#include "map.h"

struct Platform platformList[MAX_PLATFORM_LIST_SIZE] = { { 0, 0, 0, 0, {0, 0, 0, 0}, 0, 0} };
int platformCount = 0;

void Draw_AllPlatform()
{
	int i = 0;
	for (i = 0; i < MAX_PLATFORM_LIST_SIZE; i++)
	{
		if (platformList[i].visibility == 0) continue;

		CP_Settings_Fill(platformList[i].color);
		CP_Graphics_DrawRect(platformList[i].Pos.x, platformList[i].Pos.y,
			platformList[i].w, platformList[i].h);
	}
}

void Remove_Platform(struct Platform* platform)
{
	platform->visibility = 0;
}

struct Platform* Get_First_Hidden_Platform()
{
	int i = 0;
	for (i = 0; i < MAX_PLATFORM_LIST_SIZE; i++)
	{
		if (platformList[i].visibility == 0)
		{
			return &platformList[i];
		}
	}

	return NULL;
}