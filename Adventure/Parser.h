#pragma once
#include "Location.h"
#include <vector>
#include "FileReader.h"

class Parser
{
public:
	enum class commandType
	{
		MOVE = 1,
		INSPECT,
		TALK,
		USE,
		VIOLENT,//for those players that try to fuck shit up
		INVALID,
		EXIT
	};

	Parser();
	~Parser();

	commandType Parse(std::string command, std::vector<FileReader::word> verbs, std::vector<FileReader::word> nouns, std::vector<Item*> items, std::vector<Location> locations, std::vector<NPC> npcs);

	int GetItemID() const;
	int GetNPCID() const;
	int GetNounID() const;

	int FindLocationInVector(const std::string& command, const std::vector<Location> locations);

private:
	int m_ItemID = -1;
	int m_NPCID = -1;
	int m_LocationID = -1;
	int m_NounID = -1;

	int findWordInVector(const std::string& command, const std::vector<FileReader::word>& vector);
	std::vector<int> findItemInVector(const std::string& command, std::vector<Item*> vector);
	int findNPCNnVector(const std::string& command, std::vector<NPC> vector);
	

};

