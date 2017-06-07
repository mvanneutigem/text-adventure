#include "Chapter3.h"
#include "Helpers.h"
#include <iostream>
#include "Game.h"
#include "Container.h"
#include "Chapter4.h"
#include "StateMachine.h"

Chapter3::Chapter3()
{
}


Chapter3::~Chapter3()
{
}

void Chapter3::Enter()
{
}

void Chapter3::Update(FileReader& m_Reader)
{
	if (m_ConfrontedOliver)
	{
		Chapter4* CH4 = new Chapter4();
		Game::m_statemachine->ChangeState(CH4);
	}

	//purcells desk:
	if (Game::m_CurrentlocationID == 14 && Game::m_CommandType == Parser::commandType::INSPECT && Game::m_ItemID == 22 && !m_LookedAtDesk)
	{
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		Helpers::PrintSlowly("Maybe I should check the drawers now that I have a warrant.\n");
		m_LookedAtDesk = true;
	}
	if (Game::m_CurrentlocationID == 14 && Game::m_CommandType == Parser::commandType::INSPECT && Game::m_ItemID == 30 && !m_CheckedDrawers)
	{
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		Helpers::PrintSlowly("You open the drawer, a bunch of random papers, some pens and some kind of powder compact seem to be in here... wait I can see some kind of router taped to the roof of the drawer.\n");
		m_CheckedDrawers = true;
	}
	if (Game::m_CurrentlocationID == 14 && Game::m_CommandType == Parser::commandType::INSPECT && Game::m_ItemID == 28 && !m_FoundRouter && m_CheckedDrawers)
	{
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_GREEN);
		Helpers::PrintSlowly("Wireless Router added to evidence.\n");
		Item* board = m_Reader.getItems()[1];
		reinterpret_cast<Container*>(board)->AddItem(*m_Reader.getItems()[Game::m_ItemID]);
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		m_FoundRouter = true;
		Helpers::PrintSlowly("I should review the footage on my computer back in the office.\n");
	}
	if (Game::m_CurrentlocationID == 14 && Game::m_CommandType == Parser::commandType::INSPECT && Game::m_ItemID == 29 && !m_FoundPowder && m_CheckedDrawers)
	{
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_GREEN);
		Helpers::PrintSlowly("Powder compact added to evidence.\n");
		Item* board = m_Reader.getItems()[1];
		reinterpret_cast<Container*>(board)->AddItem(*m_Reader.getItems()[Game::m_ItemID]);
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		m_FoundPowder = true;
	}

	if(Game::m_CurrentlocationID == 0 && m_FoundRouter && !m_receivedCall)
	{
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_RED);
		std::cout << "BEEP BEEP BEEP .... BEEP BEEP BEEP ....\n";
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

		std::string command;
		bool invalid = true;;
		while (invalid)
		{
			getline(std::cin, command);
			if (command.find("phone") != command.npos)
			{
				if (command.find("answer") != command.npos || command.find("pick") != command.npos)
				{
					invalid = false;
				}
				else
					std::cout << "You better not mess up your phone, you just got it a week ago.\n";
			}
			else
				std::cout << "you should really answer your phone first.\n";
		}
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN);
		Helpers::PrintSlowly("Carly (The victims daughter): ");
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		Helpers::PrintSlowly("Hey " + Helpers::m_Name + ", I need to talk to you, my mother...\n she wasn't who everyone thought she was...\n Shit I have to go.\n");
		m_receivedCall = true;
	}

	if (Game::m_CurrentlocationID == 0 && m_FoundRouter && Game::m_CommandType == Parser::commandType::INSPECT && Game::m_ItemID == 5 && !m_DecodeFootage)
	{
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		Helpers::PrintSlowly("Finally a use for this old damn thing\nTime to watch this footage...\n");
		Sleep(500);
		Helpers::PrintSlowly("Strange, there doesn't seem to be anything incriminating on here...\n");
		Sleep(500);
		Helpers::PrintSlowly("What! these images are at least 1gb in data each...\n");
		Helpers::PrintSlowly("I need a password to decode these... what could it be?\n");
		std::string command;
		bool invalid = true;;
		int trys = 0;
		while (invalid)
		{
			getline(std::cin, command);
			if (command.find("carly") != command.npos || command.find("Carly") != command.npos)
			{
				Helpers::PrintSlowly( "Correct!\n");
				invalid = false;
			}
			else
			{
				Helpers::PrintSlowly("Wrong.\n");
				++trys;
				if (trys > 3)
					Helpers::PrintSlowly("Maybe it's a member of her family...\n");
			}

		}
		Helpers::PrintSlowly("the pictures decode into more video footage.\n Again, no prostitutes: instead foreign gentleman conversing intently, either on the phone or with each other.\n");
		m_DecodeFootage = true;
	}

	if (m_DecodeFootage && !m_ReceivedCallFromBoss)
	{
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_RED);
		std::cout << "BEEP BEEP BEEP .... BEEP BEEP BEEP ....\n";
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

		std::string command;
		bool invalid = true;;
		while (invalid)
		{
			getline(std::cin, command);
			if (command.find("phone") != command.npos)
			{
				if (command.find("answer") != command.npos || command.find("pick") != command.npos)
				{
					invalid = false;
				}
				else
					std::cout << "You better not mess up your phone, you just got it a week ago.\n";
			}
			else
				std::cout << "you should really answer your phone first.\n";
		}
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN);
		Helpers::PrintSlowly("Brock (your boss): ");
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		Helpers::PrintSlowly("Hey " + Helpers::m_Name + ", the background check on Oliver clears up he didn’t lose his job, he quit. \nThe financial consulting firm he worked at acquired a contract for the department \nof defense that would require all employees to do a background check.\nYes that means what you think it does\nThey must be foreign intelligence. hurry to Purcells home if you want to see the arrest.\n");
		m_ReceivedCallFromBoss = true;
	}

	if (Game::m_CurrentlocationID == 15 && !m_ConfrontedOliver && m_ReceivedCallFromBoss)
	{
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN);
		Helpers::PrintSlowly("Brock (your boss): ");
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		Helpers::PrintSlowly("Hey, you're just in time to hear his confession.\nwe cant find the girl though can you go look for her after this?\n");

		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN);
		Helpers::PrintSlowly("Oliver : ");
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		Helpers::PrintSlowly("I admit that we were agents for the Russian SVR, \nbeing a couple was part of our cover and we were ordered to conceive\n as an American born child would be a good asset. \nwe never loved each other but we both loved Carly.\n I want more for Carly than to waste her live serving a lie,\n Teri disagreed and wanted to initiate Carly but Oliver threatened to expose the operation. \n I don’t know who killed Teri but I will tell the FBI everything in return for assurance that Carly will be left alone. \nOh and you should know Geoffrey was our handler.\n");
		m_ConfrontedOliver = true;
	}

}

void Chapter3::Exit()
{
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_GREEN);
	Helpers::PrintSlowly("---------- Chapter 3 Complete -----------\n");
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
