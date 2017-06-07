#include "Chapter4.h"
#include "Helpers.h"
#include <iostream>
#include "Game.h"
#include "Chapter2.h"
#include "Container.h"

Chapter4::Chapter4()
{
}


Chapter4::~Chapter4()
{
}

void Chapter4::Enter()
{
}

void Chapter4::Update(FileReader& m_Reader)
{
	if (Game::m_CurrentlocationID == 0 && !m_gotCarlysCall)
	{
		Helpers::PrintSlowly("Carly is sitting at your desk... ");
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN);
		Helpers::PrintSlowly("Carly (The victims daughter): ");
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		Helpers::PrintSlowly("Hey " + Helpers::m_Name + ", I need to tell you something, I heard my dad is a suspect for mom's murder.\nbut... but..\nHe couldn't have done it.. I did.\n");//plottwist
		m_gotCarlysCall = true;
	}

	if(m_gotCarlysCall && !m_CarlyConfessed)
	{
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_GREEN);
		Helpers::PrintSlowly("Carly agrees to confess to the police.\n\n");
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		Helpers::PrintSlowly("the night Teri died was the same day she received the early acceptance letter from the university of Michigan.\nShe ended up argueing with her mother who wasn’t as excited as she was about it.\nTeri told her the truth: she intended for her to become a spy like herself and Oliver. \nCarly was shocked; her lifelong goal was to play soccer in college after recovering from her injury. \nShe refused to follow her mother’s plan and in the struggle that followed Teri fell and it her head on the desk,\nthen Geoffrey arrived, he saw what happened and told Carly to go home while he disposed of the body,\n he warned her that she would have to become a spy or he would tell the world that she killed Teri.\n");
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_GREEN);
		Helpers::PrintSlowly("\nSomething doesn't seem right though...\n");
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_RED);
		Helpers::PrintSlowly("BEEP BEEP BEEP .... BEEP BEEP BEEP ....\n");

		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

		std::string command;
		bool invalid = true;;
		while (invalid)
		{
			getline(std::cin, command);
			if (command.find("phone") != command.npos)
			{
				if (command.find("answer") != command.npos || command.find("pick") != command.npos || command.find("check") != command.npos)
				{
					invalid = false;
				}
			}
			else
				Helpers::PrintSlowly("you should really check your phone first.\n");
		}

		Helpers::PrintSlowly("A notification shows you finally received the autopsy report\n");
		Helpers::PrintSlowly("the first thing that stands out is an x-ray of Teri’s hand:\n showing a boxer’s fracture in  her finger bones, yet Carly said nothing about Teri punching her.\n\n wait a second... that means... \nI should talk to real killer before Carly get's locked up!\n");
		m_CarlyConfessed = true;
	}

	if(Game::m_CurrentlocationID == 17 && !m_accusedGeoffrey && Game::m_CommandType == Parser::commandType::TALK)
	{
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_GREEN);
		Helpers::PrintSlowly("It was you Geoffrey! and I have proof!\n");
		Helpers::PrintSlowly("what is the evidence that confirms geoffrey did it?\n");
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

		std::string command;
		bool invalid = true;;
		while (invalid)
		{
			getline(std::cin, command);
			if (command.find("pen") != command.npos)
			{
				SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_GREEN);
				Helpers::PrintSlowly(" When you send Carly home Teri wasn’t dead yet,\n just unconscious. you decided rather a more valuable asset in Carly\nso you retired Teri. you bludgeoned her to death, \nTeri fought back fracturing her hand in the process, \nand trying to stab you with the fountain pen, the pen was filled with invisible ink\n which can be found all over your shirt!\n");
				invalid = false;
			}
			else
				Helpers::PrintSlowly("that doesn't proof anything... try something else...\n");
		}
		m_accusedGeoffrey = true;

		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		Helpers::PrintSlowly("Congratulations you solved the case!\nCarly and Oliver are taken into witness protection and Geoffrey gets 20 years.\n And maybe your boss will let you handle some more cases now.\n");
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_GREEN);
		Helpers::PrintSlowly("---------- Game Completed -----------\n");
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		Helpers::PrintSlowly("type exit to exit game, or wander around some more if you want.\n");
	}

}

void Chapter4::Exit()
{
}
