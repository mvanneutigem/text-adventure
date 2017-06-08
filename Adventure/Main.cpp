#include <iostream>
//#define _CRTDBG_MAP_ALLOC  
//#include <stdlib.h>  
//#include <crtdbg.h>  

#include "Game.h"
#include "StateMachine.h"
#include "Chapter1.h"
using namespace std;

StateMachine* statemachine;
Game game;

BOOL ctrl_handler(DWORD event)
{
	if (event == CTRL_CLOSE_EVENT)
	{
		//cleanup
		delete statemachine;
		game.m_Reader.Destroy();
	}
	return TRUE;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrl_handler, true);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//_CrtSetBreakAlloc(170);
	//_crtBreakAlloc = 159;


	statemachine = new StateMachine();
	game.Start(statemachine);
	Helpers::RunIntroduction();
	Chapter1 CH1;
	statemachine->ChangeState(&CH1);

	while(!game.m_ExitGame)
	{
		game.Update();
	}

	delete statemachine;

	return 0;
}
