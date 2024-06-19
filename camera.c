#include "camera.h"

enum
{
	CAMERA_MOVEMENT = 200
};

struct Camera camera = { {0, 0} };

void Move_Camera(float x, float y)
{
	float t = CP_System_GetDt();
	camera.pos.x += x * t;
	camera.pos.y += y * t;
}

void Update_Camera()
{
	if (CP_Input_KeyDown(KEY_A))
	{
		Move_Camera(CAMERA_MOVEMENT, 0);
	}

	if (CP_Input_KeyDown(KEY_D))
	{
		Move_Camera(-CAMERA_MOVEMENT, 0);
	}

	if (CP_Input_KeyDown(KEY_W))
	{
		Move_Camera(0, CAMERA_MOVEMENT);
	}

	if (CP_Input_KeyDown(KEY_S))
	{
		Move_Camera(0, -CAMERA_MOVEMENT);
	}

	CP_Settings_Translate(camera.pos.x, camera.pos.y);
}

