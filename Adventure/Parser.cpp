#include "Parser.h"
#include <iostream>
#include <algorithm>
#include "Game.h"

using namespace std;

Parser::Parser()
{
}


Parser::~Parser()
{
}

vector<int> Parser::findItemInVector(const string& command, vector<Item*> vector)
{
	std::vector<int> itVec;
	auto counter = 0;
	int ID = -1;
	auto lambda = [&](Item* w) {
		if (command.find(w->GetKeyword()) != command.npos)
		{
			ID = counter;
			itVec.push_back(ID);
		}
		++counter; };

	for_each(vector.begin(), vector.end(), lambda);//lambda for no good reason
	//return ID;
	return itVec;
}

int Parser::findNPCNnVector(const std::string& command, std::vector<NPC> vector)
{
	auto counter = 0;
	int ID = -1;
	auto lambda = [&](NPC w) {
		if (command.find(w.GetName()) != command.npos)
		{
			ID = counter;
		}
		++counter; };

	for_each(vector.begin(), vector.end(), lambda);//lambda for no good reason
	return ID;
}

int Parser::findWordInVector(const string& command, const vector<FileReader::word>& vector)
{
	auto counter = 0;
	int ID = -1;
	auto lambda = [&](FileReader::word w) {
		if (command.find(w.wordStr) != command.npos)
		{
			ID = w.ID;
		}
		++counter; };

	for_each(vector.begin(), vector.end(), lambda);//another lambda for no good reason

	if (ID == -1)
	{

	}

	return ID;
}

int Parser::FindLocationInVector(const string& command, const vector<Location> locations)
{
	auto counter = 0;
	int ID = -1;
	auto lambda = [&](Location w) {
		if (command.find(w.GetKeyword()) != command.npos)
		{
			ID = counter;
		}
		++counter; };

	for_each(locations.begin(), locations.end(), lambda);//lambda for no good reason
	return ID;
}

Parser::commandType Parser::Parse(std::string command, std::vector<FileReader::word> verbs, std::vector<FileReader::word> nouns, std::vector<Item*> items, std::vector<Location> locations, std::vector<NPC> npcs)
{
	auto verb = -1;
	m_LocationID = -1;
	m_ItemID = -1;
	m_NounID = -1;
	m_NPCID = -1;

	verb = findWordInVector(command, verbs);
	m_NounID = findWordInVector(command, nouns);
	if (m_NounID == -1 && verb != -1)
	{
		//instead == make nouns also contain keys and then compare them to keys of locations, items etc.
		
		auto foundItems = findItemInVector(command, items);
		for(auto i = 0; i < foundItems.size(); ++i)
		{
			if (items[foundItems[i]]->IsAtLocation(Game::m_CurrentlocationID) || items[foundItems[i]]->IsCarrying())
			{
				m_ItemID = foundItems[i];
			}
		}
		
		m_LocationID = FindLocationInVector(command, locations);
		m_NPCID = findNPCNnVector(command, npcs);
	}

	if (m_ItemID != -1)
	{
/*		if (!items[m_ItemID]->IsAtLocation(Game::m_CurrentlocationID) && !items[m_ItemID]->IsCarrying())
		{
			m_ItemID = -1;
			m_NPCID = -1;
			cout << "this can't be found here.\n";
		}
		else */if (m_NPCID != -1)
		{
			if(verb == 3)
			{
				m_ItemID = -1;
			}
			else if (verb == 2)
			{
				m_NPCID = -1;
			}
		}
	}
	else
	{
		m_NPCID = -1;
	}

	if (m_LocationID != -1)
	{
		auto x = locations[Game::m_CurrentlocationID];
		if (x.goBack() == m_LocationID)
			m_NounID = 4;
		if (x.goRight() == m_LocationID)
			m_NounID = 2;
		if (x.goLeft() == m_LocationID)
			m_NounID = 1;
		if (x.goForward() == m_LocationID)
			m_NounID = 3;
	}

	if (verb == -1 && (m_NounID == -1 || m_ItemID == -1))
	{
		if (command == "exit" || command == "quit")
		{
			return commandType::EXIT;
		}
		else
		{
			cout << "unrecognized command.\n";
			return commandType::INVALID; 
		}
	}
	else
	{
		return commandType(verb);
		
	}
	
}

int Parser::GetItemID() const
{
	return m_ItemID;
}

int Parser::GetNPCID() const
{
	return m_NPCID;
}

int Parser::GetNounID() const
{
	return m_NounID;
}
