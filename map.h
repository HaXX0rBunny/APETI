#pragma once

#include "collision.h"
#include "platform.h"

enum
{
	MAX_PLATFORM_LIST_SIZE = 100
};

enum Direction
{
	Up = 0,
	Right = 1,
	Down = 2,
	Left = 3
};

void Draw_AllPlatform();

void Remove_Platform(struct Platform* platform);

struct Platform* Get_First_Hidden_Platform();