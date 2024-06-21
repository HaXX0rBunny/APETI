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
#include "game.h"

const int window_width = 1600;
const int window_height = 900;

int main(void)
{

	CP_System_SetWindowSize(window_width, window_height);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}
