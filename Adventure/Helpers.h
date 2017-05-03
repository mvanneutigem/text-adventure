#include <windows.h>
#include <string>
#pragma once
class Helpers
{
public:
	Helpers();
	~Helpers();
	static HANDLE m_hdstout;
	static void PrintSlowly(std::string text);
	static void RunIntroduction();
	static std::string m_Name;
};

