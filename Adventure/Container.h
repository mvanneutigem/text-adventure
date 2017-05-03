#pragma once
#include <vector>
#include "Item.h"
#include <iostream>

class Container : public Item
{
public:
	Container(const std::string& name, const std::string& keyword, const std::string& description, const std::vector<int> locations):
	Item(name,keyword,description,false,locations){}
	~Container(){};

	void AddItem(Item i)
	{
		Items.push_back(i);
		i.SetLocation(m_LocationIndexArr[0]);
	}

	void RemoveItem(int index)
	{
		Items.erase(Items.begin() + index);
	}


private:
	std::vector<Item> Items;

	friend std::ostream & operator<<(std::ostream& os, Container* s);
};

inline std::ostream& operator<<(std::ostream& os, Container* s)
{
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN);
	Helpers::PrintSlowly(s->m_Name + "\n");
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	Helpers::PrintSlowly(s->m_Description + "\n");
	Helpers::PrintSlowly("Evidence: \n");
	for(auto i : s->Items)
	{
		Helpers::PrintSlowly("\t" + i.GetKeyword() + "\n");
	}

	return os;
}