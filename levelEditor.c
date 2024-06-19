#include "levelEditor.h"
#include "player.h"

extern const int window_width;
extern const int window_height;
extern struct Platform platformList[MAX_PLATFORM_LIST_SIZE];

void Edit_Delete_Platform(void)
{
	if (CP_Input_MouseDown(MOUSE_BUTTON_RIGHT))
	{
		struct Platform* platform = Platform_Mouse_Collision();
		if (platform != NULL)
		{
			Remove_Platform(platform);
		}
	}
}

void Edit_Add_Platform(void)
{
	const int numberOfTilesW = 50;
	const int numberOfTilesH = 30;

	int platformW = window_width / numberOfTilesW;
	int platformH = window_height / numberOfTilesH;

	int mouseX = (int)floor(CP_Input_GetMouseWorldX());
	int mouseY = (int)floor(CP_Input_GetMouseWorldY());

	int gridCoordX = mouseX / platformW;
	int gridCoordY = mouseY / platformH;

	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
	{
		if (Platform_Mouse_Collision() != NULL)
			return;

		struct Platform* platform = Get_First_Hidden_Platform();

		if (platform == NULL)
			return;

		Initialize_Platform(platform, (float)(gridCoordX * platformW), (float)(gridCoordY * platformH),
			(float)platformW, (float)platformH, CP_Color_Create(0, 0, 0, 255), 0, 1);
	}
}

void Edit_Grid(void)
{
	Edit_Delete_Platform();
	Edit_Add_Platform();
}

struct Platform* Platform_Mouse_Collision()
{
	for (int i = 0; i < MAX_PLATFORM_LIST_SIZE; i++)
	{
		struct Platform* platform = &platformList[i];

		if (!platform->visibility) continue;

		if (Platform_MouseIn(platform))
		{
			return platform;
		}
	}

	return NULL;
}

void level_editor_state_init(void)
{
	Load_Level_From_File("myLevel.lvl");
}

void level_editor_state_update(void)
{
	CP_Color color_white = CP_Color_Create(255, 255, 255, 255);
	CP_Graphics_ClearBackground(color_white);

	Draw_AllPlatform();
	Player_Update();
	Player_Draw();

	//edit mode text

	Edit_Grid();
}

void level_editor_state_exit(void)
{
	Save_Level_To_File("myLevel.lvl");
}