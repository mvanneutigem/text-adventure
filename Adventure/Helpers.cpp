#include "Helpers.h"
#include <iostream>

std::string Helpers::m_Name = "";
HANDLE Helpers::m_hdstout = GetStdHandle(STD_OUTPUT_HANDLE);
Helpers::Helpers()
{
}


Helpers::~Helpers()
{
}

void Helpers::PrintSlowly(std::string text)
{
	auto str = text.c_str();
	int len = strlen(str);
	for(auto i = 0; i < len; ++i)
	{
		putchar(str[i]);
		Sleep(50);
	}
}

void Helpers::RunIntroduction()
{
	PrintSlowly("Before you go on this adventure, I'd like to know something;\nWhat is your name?\n");
	std::string name;
	bool sure = false;
	while(!sure)
	{
		getline(std::cin, name);
		PrintSlowly("Are you sure that " + name + " is correct?\n");
		std::string answer;
		getline(std::cin, answer);
		if (answer.find("y") != answer.npos || answer.find("jup") != answer.npos)
		{
			m_Name = name;
			sure = true;
		}
		else
			PrintSlowly("Please enter your new name\n");
	}
	PrintSlowly("Alright, " + m_Name + ", let's start your adventure.");
	Sleep(1000);
	system("cls");
}
