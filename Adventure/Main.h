#pragma once
#include <string>

class Main
{
public:
	Location(std::string name, std::string description);
	~Location();

	void PrintDescription();

private:
	std::string m_Name;
	std::string m_Description;
	friend std::ostream & operator<<(std::ostream& os, Location s);
};

inline std::ostream& operator<<(std::ostream& os, Location s)
{
	os << "" << s.m_Name << std::endl;
	os << "" << s.m_Description << std::endl;
	return os;
}