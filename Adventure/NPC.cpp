#include "NPC.h"
#include <iostream>
#include "Helpers.h"

NPC::NPC(std::string name, std::vector<Dialogue> interactions):
m_Name(name),
m_interactions(interactions)
{
}

NPC::~NPC()
{
}

void NPC::talkTo(const int ID)
{
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN);
	Helpers::PrintSlowly(m_Name);
	SetConsoleTextAttribute(Helpers::m_hdstout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	Helpers::PrintSlowly(":" + m_interactions[ID].text + "\n");
}

std::string NPC::GetName()
{
	return m_Name;
}
