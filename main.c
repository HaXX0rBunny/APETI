//---------------------------------------------------------
// file:	main.c
// author:	[NAME]
// email:	[DIGIPEN EMAIL ADDRESS]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright ?2020 DigiPen, All rights reserved.
//---------------------------------------------------------
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#include "cprocessing.h"
#include "logo.h"
#include "levelEditor.h"

const int window_width = 1600;
const int window_height = 900;

int main(void)
{
	CP_System_SetWindowSize(window_width, window_height);
	//CP_Engine_SetNextGameState(level_editor_state_init, level_editor_state_update, level_editor_state_exit);
	CP_Engine_SetNextGameState(logo_init, logo_update, logo_exit);
	CP_Engine_Run();
	return 0;
}
