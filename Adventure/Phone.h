#pragma once
#include "Item.h"
#include "FileReader.h"

class Parser;

class Phone : public Item
{
public:
	Phone(const std::string& name, const std::string& keyword, const std::string& description, bool carryable, const std::vector<int> locations);
	~Phone();
	void Use(Parser p, FileReader f);
private:
	bool m_UnlockedGeoffrey = false;
};

