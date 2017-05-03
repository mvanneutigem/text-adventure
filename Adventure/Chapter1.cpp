#include "Chapter1.h"
#include "Helpers.h"
#include <iostream>
#include "Game.h"
#include "Chapter2.h"
#include "Container.h"
using namespace std;

Chapter1::Chapter1()
{
}

Chapter1::~Chapter1()
{
}

void Chapter1::Enter()
{
	Helpers::PrintSlowly(Helpers::m_Name + ": Hmmm...I really want some coffee and maybe some donuts,\nthere's no cases right now so I wonder if I could slip away and go get some...\n");
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_RED);
	cout << "BEEP BEEP BEEP .... BEEP BEEP BEEP ....\n";
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	Helpers::PrintSlowly( Helpers::m_Name + ": My god, I almost got a heart attack,\nI should really change my ringtone...\n");
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_RED);
	cout << "BEEP BEEP BEEP .... BEEP BEEP BEEP ....\n";
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	string command;
	bool invalid = true;;
	while (invalid)
	{
		getline(cin, command);
		if (command.find("phone") != command.npos)
		{
			if (command.find("answer") != command.npos || command.find("pick") != command.npos)
			{
				invalid = false;
			}
			else
				cout << "You better not mess up your phone, you just got it a week ago.\n";
		}
		else
			cout << "you should really answer your phone first.\n";
	}

	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN);
	Helpers::PrintSlowly("Brock (your boss): ");
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	Helpers::PrintSlowly("Hey " + Helpers::m_Name + ", a body was found in the basement of the upstate hotel\nI've decided to give you a chance, you're on the case,\nyou better not screw this up or it will be your LAST case!\nI know you don't have a car so just book an uber with your phone or something.\nSee you in a few.\n");
	Sleep(500);
}

void Chapter1::Update(FileReader m_Reader)
{
	if (m_EnteredCrimeScene && m_gotPreliminaryReport)
	{
		auto CH2 = new Chapter2();
		Game::m_statemachine->ChangeState(CH2);
	}

	if (Game::m_CurrentlocationID == 8 && !m_EnteredCrimeScene)//crime scene
	{
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN);
		Helpers::PrintSlowly("Brock (your boss): ");
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		Helpers::PrintSlowly("Hey " + Helpers::m_Name + ", finally you're here.\nThe body is in there, take a good look around, you might find some evidence.\nThen go talk to dalton at the morgue, he'll be able to tell you more about the victim.\n");
		m_EnteredCrimeScene = true;
	}

	if (Game::m_CurrentlocationID == 2 && Game::m_CommandType == Parser::commandType::TALK && !m_gotPreliminaryReport)//crime scene
	{
		Game::m_TalkID = 1;
		m_gotPreliminaryReport = true;
	}
	else
		Game::m_TalkID = 0;

	//crime scene
	if (Game::m_CurrentlocationID == 9 && Game::m_CommandType == Parser::commandType::INSPECT && Game::m_ItemID == 14 && !m_SeenMachine)//crime scene
	{
		Helpers::PrintSlowly("The laundry machine where the body was found contains a pen and a bedsheet.\n");
		m_SeenMachine = true;
	}
	if (Game::m_CurrentlocationID == 9 && Game::m_CommandType == Parser::commandType::INSPECT && Game::m_ItemID == 16 && !m_CollectedEvidence01)//crime scene
	{
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_GREEN);
		Helpers::PrintSlowly(m_Reader.getItems()[Game::m_ItemID]->GetKeyword() + " added to evidence.\n");
		Item* board = m_Reader.getItems()[1];
		reinterpret_cast<Container*>(board)->AddItem(*m_Reader.getItems()[Game::m_ItemID]);
		m_CollectedEvidence01 = true;
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
	if (Game::m_CurrentlocationID == 9 && Game::m_CommandType == Parser::commandType::INSPECT && Game::m_ItemID == 17 && !m_CollectedEvidence02)//crime scene
	{
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_GREEN);
		Helpers::PrintSlowly(m_Reader.getItems()[Game::m_ItemID]->GetKeyword() + " added to evidence.\n");
		Item* board = m_Reader.getItems()[1];
		reinterpret_cast<Container*>(board)->AddItem(*m_Reader.getItems()[Game::m_ItemID]);
		m_CollectedEvidence02 = true;
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
	if (Game::m_CurrentlocationID == 9 && Game::m_CommandType == Parser::commandType::INSPECT && Game::m_ItemID == 18 && !m_CollectedEvidence03)//crime scene
	{
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_GREEN);
		Helpers::PrintSlowly(m_Reader.getItems()[Game::m_ItemID]->GetKeyword() + " added to evidence.\n");
		Item* board = m_Reader.getItems()[1];
		reinterpret_cast<Container*>(board)->AddItem(*m_Reader.getItems()[Game::m_ItemID]);
		m_CollectedEvidence03 = true;
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
}

void Chapter1::Exit()
{
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_GREEN);
	Helpers::PrintSlowly("---------- Chapter 1 Complete -----------\n");
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	Helpers::PrintSlowly("Unlocked:\nTeri Purcell's home\nTeri Purcell's Office.\n");
}
