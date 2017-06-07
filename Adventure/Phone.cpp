#include "Phone.h"
#include <vector>
#include <string>
#include <iostream>
#include "Parser.h"
#include "Game.h"
#include "Chapter1.h"
#include "StateMachine.h"
using namespace std;


Phone::Phone(const std::string& name, const std::string& keyword, const std::string& description, bool carryable, const std::vector<int> locations): 
Item(name,keyword, description,carryable, locations)
{
	m_UnlockedGeoffrey = false;
}


Phone::~Phone()
{
}

void Phone::Use(Parser p, FileReader f)
{
	Helpers::PrintSlowly("What app would you like to access?\n");
	bool retry = true;
	string command;
	getline(cin, command);
	if (command.find("outlook") != command.npos)
	{
		Helpers::PrintSlowly("Your latest e-mails: \n\n");
		//add post morten if in chapter 5
		Helpers::PrintSlowly("Polder Casino		notification about your acc... \n");
		Helpers::PrintSlowly("Nero news		Pay for 1, get 6! \n");
		Helpers::PrintSlowly("Playstation		Thanks for your purchase. \n\n");

		Helpers::PrintSlowly("You should really clean up your inbox... \n");
	}
	else if (command.find("maps") != command.npos || command.find("uber") != command.npos)
	{
		Helpers::PrintSlowly("Available locations: \n\n");
		if (dynamic_cast<Chapter1*>(Game::m_statemachine->GetCurrentState()) == NULL)//make sure chapter 1 is not active
		{
			Helpers::PrintSlowly("purcells home			This is where the victim lived. \n");
			Helpers::PrintSlowly("purcells office			This is where the victim worked. \n");
			if (m_UnlockedGeoffrey)
			{
				Helpers::PrintSlowly("silvers office			This is Geoffrey silvers office. \n");
			}
		}
		Helpers::PrintSlowly("police office			This is where your desk is at. \n");
		Helpers::PrintSlowly("The Upstate hotel		This is the crime scene. \n");
		Helpers::PrintSlowly("The lab				This is where you can get your samples checked.\n");
		Helpers::PrintSlowly("The morgue			This is where you can get a post mortem.\n\n");

		Helpers::PrintSlowly("book uber to where?\n");
		getline(cin, command);

		int index = p.FindLocationInVector(command, f.getLocations());
		if (index != -1)
		{
			Helpers::PrintSlowly( "Fast travelling to " + f.getLocations()[index].GetKeyword());
			Game::m_CurrentlocationID = index;

		}
	}
	else if (command.find("database") != command.npos && dynamic_cast<Chapter1*>(Game::m_statemachine->GetCurrentState()) == NULL)
	{
		Helpers::PrintSlowly("Look up something in the police database? \n\n");
		getline(cin, command);
		if (command.find("y") != command.npos)
		{
			Helpers::PrintSlowly("What would you like to look up?\n");
			getline(cin, command);
			if (command.find("plate") != command.npos)
			{
				Helpers::PrintSlowly("The plate seems to belong to Geoffrey Silver\n");
				Helpers::PrintSlowly("Unlocked: silvers office.\n");
				m_UnlockedGeoffrey = true;
			}
		}
	}
	else
	{
		Helpers::PrintSlowly("Now is not the time for this app.");
	}
}
