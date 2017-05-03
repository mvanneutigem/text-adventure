#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Game.h"
#include "StateMachine.h"
#include "Chapter1.h"
using namespace std;


void main()
{
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	auto statemachine = new StateMachine();
	game.Start(statemachine);
	Helpers::RunIntroduction();
	Chapter1 CH1;
	statemachine->ChangeState(&CH1);

	while(!game.m_ExitGame)
	{
		game.Update();
	}

	delete statemachine;
	cin.get();
}
