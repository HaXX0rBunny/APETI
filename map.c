#include "map.h"

struct Platform platformList[MAX_PLATFORM_LIST_SIZE];
int platformCount = 0;

extern struct Camera camera;

void Draw_AllPlatform()
{
	int i = 0;
	for (i = 0; i < MAX_PLATFORM_LIST_SIZE; i++)
	{
		if (platformList[i].exist == 0) continue;
		
		CP_Settings_Fill(platformList[i].color);
		CP_Graphics_DrawRect(platformList[i].Pos.x, platformList[i].Pos.y,
			platformList[i].w, platformList[i].h);
	}
}

void Clear_Map()
{
	int i = 0;
	for (i = 0; i < MAX_PLATFORM_LIST_SIZE; i++)
	{
		if (platformList[i].exist == 0) continue;
		Remove_Platform(&platformList[i]);
	}
}

void Remove_Platform(struct Platform* platform)
{
	platform->exist = 0;
	platformCount--;
}

struct Platform* Get_First_Hidden_Platform()
{
	int i = 0;
	for (i = 0; i < MAX_PLATFORM_LIST_SIZE; i++)
	{
		if (platformList[i].exist == 0)
		{
			return &platformList[i];
		}
	}

	return NULL;
}