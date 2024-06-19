#pragma once

#include <math.h>
#include "levelSaver.h"

void Edit_Delete_Platform(void);
void Edit_Add_Platform(void);
void Edit_Grid(void);

struct Platform* Platform_Mouse_Collision();

void level_editor_state_init(void);
void level_editor_state_update(void);
void level_editor_state_exit(void);