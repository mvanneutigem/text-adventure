#pragma once
#include <string>
#include <vector>
#include "Location.h"
#include "Item.h"
#include "NPC.h"

class FileReader
{
public:
	struct word
	{
		int ID;
		std::string wordStr;
	};

	FileReader();
	~FileReader();
	void readLocations(const std::string& filename);
	void readInput(const int startpos, int& endpos, std::string line, std::string& save, const char separater);
	void readWordIntoVector(const std::string& filename, std::vector<word>& words);
	void readItems(const std::string& filename);
	void readNPCs(const std::string& filename);

	void readVerbs(const std::string& filename);
	void readNouns(const std::string& filename);

	std::vector<Item*>& getItems();//pointers to avoid slicing (derived object stored in base vector)
	const std::vector<Location>& getLocations() const;
	const std::vector<word>& getVerbs() const;
	const std::vector<word>& getNouns() const;
	const std::vector<NPC>& getNPCs() const;

private:
	std::vector<Item*> m_Items;
	std::vector<NPC> m_NPCs;
	std::vector<Location> m_Locations;
	std::vector<word> m_Verbs;
	std::vector<word> m_Nouns;
};

