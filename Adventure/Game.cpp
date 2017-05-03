#include "Game.h"
#include <iostream>
#include "Parser.h"
#include "Phone.h"
#include "StateMachine.h"
#include "Container.h"
using namespace std;

int Game::m_CurrentlocationID = 0;
Parser::commandType Game::m_CommandType = Parser::commandType::INVALID;
int Game::m_TalkID = 0;
int Game::m_ItemID = 0;
StateMachine* Game::m_statemachine = nullptr;

Game::Game()
{
}


Game::~Game()
{
}

void Game::Start(StateMachine* machine)
{
	m_statemachine = machine;
	m_Reader.readLocations("resources/locations.txt");
	m_Reader.readVerbs("resources/verbs.txt");
	m_Reader.readNouns("resources/nouns.txt");
	m_Reader.readItems("resources/items.txt");
	m_Reader.readNPCs("resources/npc.txt");
}

void Game::Update()
{
	ShowCurrentLocation();
	m_statemachine->GetCurrentState()->Update(m_Reader);

	//getinput
	string command;
	auto retry = true;
	while (retry)
	{
		getline(cin, command);
		m_CommandType = parser.Parse(command, m_Reader.getVerbs(), m_Reader.getNouns(), m_Reader.getItems(), m_Reader.getLocations(), m_Reader.getNPCs());
		if (m_CommandType == Parser::commandType::INVALID)
		{
			retry = true;
			cout << "Wait what? I have like no idea what you're trying to do here.\n";
		}
		else
			retry = false;
	}
	m_statemachine->GetCurrentState()->Update(m_Reader);
	ShowCurrentLocation();

	switch (m_CommandType)
	{
	case Parser::commandType::MOVE:
		switch (direction(parser.GetNounID()))
		{
		case direction::left:
			handleMovement(direction::left, m_CurrentlocationID, m_Reader.getLocations());
			break;
		case direction::right:
			handleMovement(direction::right, m_CurrentlocationID, m_Reader.getLocations());
			break;
		case direction::forward:
			handleMovement(direction::forward, m_CurrentlocationID, m_Reader.getLocations());
			break;
		case direction::back:
			handleMovement(direction::back, m_CurrentlocationID, m_Reader.getLocations());
			break;
		default:
			cout << "Wherever you're trying to go, you can't.\n";
			break;
		}
		break;
	case Parser::commandType::TALK:
		HandleTalking();
		break;
	case Parser::commandType::USE:
		HanleUsage();
		break;
	case Parser::commandType::INSPECT:
		HandleInspection();
		break;
	case Parser::commandType::VIOLENT:
		Helpers::PrintSlowly("Why are you so violent?\nmaybe you should go outside and kick a tree or something\nGame will timeout untill you've cooled down a little bit.\n");
		Sleep(30000);
		Helpers::PrintSlowly("You may continue now.\n");
		break;
	case Parser::commandType::EXIT:
		m_ExitGame = true;
		break;
	default:
		cout << "at this stage this command is not handled yet #sadlife, try something else.\n";
		break;
	}
}

void Game::ShowCurrentLocation()
{
	if (m_CurrentlocationID != m_LastLocationID)
	{
		cout << "\nYou are now at " << m_Reader.getLocations()[m_CurrentlocationID] << endl;
		m_LastLocationID = m_CurrentlocationID;
	}
}

void Game::HandleTalking()
{
	auto npcs = m_Reader.getNPCs();
	auto NPCID = parser.GetNPCID();
	if (NPCID != -1)
		npcs[NPCID].talkTo(m_TalkID);
	else
		cout << "Yo, stop talking to yourself, people will think you craycray.";
}

void Game::HanleUsage()
{
	m_ItemID = parser.GetItemID();
	if (m_ItemID == 0 )
	{
		Item* i = m_Reader.getItems()[m_ItemID];
		reinterpret_cast<Phone*>(i)->Use(parser,m_Reader);
	}
}

void Game::HandleInspection()
{
	m_ItemID = parser.GetItemID();
	if (m_ItemID !=-1)
	{
		if (m_ItemID != 1)
			cout << *m_Reader.getItems()[m_ItemID];
		else
		{
			Item* board = m_Reader.getItems()[m_ItemID];
			Container* b= reinterpret_cast<Container*>(board);
			cout << b;
		}
	}
	else
	{
		cout << "Forreal what are you trying to even look at.";
	}
	
}

void Game::handleMovement(const direction direction, int& currentLocation, const vector<Location> locations)
{
	auto templocation = -1;
	switch (direction)
	{
	case direction::left:
		templocation = locations[currentLocation].goLeft();
		if (templocation != -1)
			currentLocation = templocation;
		else
			cout << "yeah uhm I can't go left here...\n";
		break;
	case direction::right:
		templocation = locations[currentLocation].goRight();
		if (templocation != -1)
			currentLocation = templocation;
		else
			cout << "you can't go right here dude.\n";
		break;
	case direction::forward:
		templocation = locations[currentLocation].goForward();
		if (templocation != -1)
			currentLocation = templocation;
		else
			cout << "going forward here doesn't seem to bring you anywhere.\n";
		break;
	case direction::back:
		templocation = locations[currentLocation].goBack();
		if (templocation != -1)
			currentLocation = templocation;
		else
			cout << "there is no going back now.\n";
		break;
	default:;
	}
}
