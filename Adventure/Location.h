#pragma once
#include <string>
#include "Helpers.h"

class Location
{
public:
	Location(const std::string& name, const std::string& keyword, const std::string& description, const int left, const int right, const int forward, const int back);
	Location(const std::string& name, const std::string& keyword, const std::string& description, const int left, const int right, const int forward, const int back, bool unlocked):
		m_Unlocked(unlocked),
		m_Name(name),
		m_keyword(keyword),
		m_Description(description),
		m_Left(left),
		m_Right(right),
		m_Forward(forward),
		m_Back(back)

	{
	}

	~Location();

	void PrintDescription() const;
	int goLeft() const;
	int goRight() const;
	int goForward() const;
	int goBack() const;
	std::string GetKeyword() const { return m_keyword; };

private:
	std::string m_Name;
	std::string m_keyword;
	std::string m_Description;
	bool m_Unlocked = false;
	int m_Left;
	int m_Right;
	int m_Forward;
	int m_Back;
	friend std::ostream & operator<<(std::ostream& os, const Location s);
};

inline std::ostream& operator<<(std::ostream& os, Location s)
{
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN);
	Helpers::PrintSlowly(s.m_Name + "\n");
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	Helpers::PrintSlowly(s.m_Description + "\n");
	return os;
}