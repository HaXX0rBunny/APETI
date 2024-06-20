#pragma once

#include <math.h>
#include "levelSaver.h"
#include "game.h"

void Edit_Delete_Platform(void);
void Edit_Add_Platform(void);
void Edit_Grid(void);

void Edit_Update_Text(void);

void Edit_Change_Mode(void);

struct Platform* Platform_Mouse_Collision();

void level_editor_state_init(void);
void level_editor_state_update(void);
void level_editor_state_exit(void);