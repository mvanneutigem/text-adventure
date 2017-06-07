#include "Chapter2.h"
#include "Helpers.h"
#include "Game.h"
#include "Container.h"
#include "Chapter3.h"
#include "Chapter1.h"
#include "StateMachine.h"


Chapter2::Chapter2()
{
}


Chapter2::~Chapter2()
{
}

void Chapter2::Enter()
{
}

void Chapter2::Update(FileReader& m_Reader)
{
	if (m_ReceivedCall && m_FoundBloodstain)
	{
		Chapter3* CH3 = new Chapter3();
		Game::m_statemachine->ChangeState(CH3);
	}

	if (m_TalkedToSilver && !m_ReceivedCall)
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
		Helpers::PrintSlowly("Hey " + Helpers::m_Name + ", we got a new lead!\nPurcell banned a series of prostitutes who frequented the hotel and later receives anonymous death threats from their pimps.\nBut I made a trip to vice and turns out Purcell was a facilitator for their work at the hotel,\nshe even sabotaged the cameras in the basement giving the girls safe access in and out of the hotel,\n the strange part is that she never took a cut of their earnings; she was basically a volunteer.\n I think you should go back to her office, maybe you missed something? you've got a warrant now. \n");
		m_ReceivedCall = true;
	}

	if (Game::m_CurrentlocationID == 14 && Game::m_CommandType == Parser::commandType::INSPECT && Game::m_ItemID == 22 && !m_LookedAtDesk)
	{
		Helpers::PrintSlowly("There seems to be a stain of some kind on the corner of the desk...\n");
		m_LookedAtDesk = true;
	}
	if (Game::m_CurrentlocationID == 14 && Game::m_CommandType == Parser::commandType::INSPECT && Game::m_ItemID == 23 && !m_FoundBloodstain)
	{
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_GREEN);
		Helpers::PrintSlowly("Blood stain added to evidence.\n");
		Item* board = m_Reader.getItems()[1];
		reinterpret_cast<Container*>(board)->AddItem(*m_Reader.getItems()[Game::m_ItemID]);
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		m_FoundBloodstain = true;
	}
	if (Game::m_CurrentlocationID == 15 && Game::m_CommandType == Parser::commandType::INSPECT && Game::m_ItemID == 24 && !m_InspectedCouch)
	{
		m_InspectedCouch = true;
		Helpers::PrintSlowly("The neighbour keeps looking inside... Strange...\n");
	}
	if (Game::m_CurrentlocationID == 15 && Game::m_CommandType == Parser::commandType::INSPECT && Game::m_ItemID == 25 && !m_FoundLetter)
	{
		m_FoundLetter = true;
	}
	if(Game::m_CurrentlocationID == 15 && Game::m_CommandType == Parser::commandType::TALK && (m_InspectedCouch ||m_FoundLetter) )
	{
		Game::m_TalkID = 1;
	}
	if (Game::m_CurrentlocationID == 16 && Game::m_CommandType == Parser::commandType::TALK && !m_TalkedToNeighbour)
	{
		Game::m_TalkID = 1;
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_GREEN);
		Helpers::PrintSlowly("Picture of license plate added to evidence.\n");
		Item* board = m_Reader.getItems()[1];
		reinterpret_cast<Container*>(board)->AddItem(*m_Reader.getItems()[26]);
		SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		Helpers::PrintSlowly("Use your phone to look up plates in the police database\n");
		m_TalkedToNeighbour = true;
	}
	if (Game::m_CurrentlocationID == 17 && Game::m_CommandType == Parser::commandType::TALK && !m_TalkedToSilver)
	{
		Game::m_TalkID = 1;
		m_TalkedToSilver = true;
	}
}

void Chapter2::Exit()
{
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_GREEN);
	Helpers::PrintSlowly("---------- Chapter 2 Complete -----------\n");
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
