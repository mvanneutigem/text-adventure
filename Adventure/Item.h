#pragma once
#include <string>
#include <vector>
#include "Helpers.h"

class Item
{
public:
	Item(const std::string& name, const std::string& keyword, const std::string& description, bool carryable,const std::vector<int> locations);
	virtual ~Item();

	void SetLocation(int ID)
	{
		m_LocationIndexArr.clear(); 
		m_LocationIndexArr.push_back(ID);
	}

	bool IsAtLocation(const int ID) const;
	std::string GetKeyword() const;
	bool IsCarrying() const;
	void Use();
protected:
	std::string m_Name;
	std::string m_keyword;
	std::string m_Description;
	std::string m_Action;
	bool m_IsCarrying;
	std::vector<int> m_LocationIndexArr;
	friend std::ostream & operator<<(std::ostream& os, Item s);
};

inline std::ostream& operator<<(std::ostream& os, Item s)
{
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN);
	Helpers::PrintSlowly(s.m_Name + "\n");
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	Helpers::PrintSlowly(s.m_Description + "\n");
	return os;
}