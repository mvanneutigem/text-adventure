#pragma once
#include <string>
#include <vector>

class NPC
{
public:
	struct Dialogue
	{
		int ID;
		std::string text;
	};
	NPC(std::string name, std::vector<Dialogue> interactions);
	~NPC();

	void talkTo(const int ID);
	std::string	GetName();

private:
	std::string m_Name;
	std::vector<Dialogue> m_interactions;
};

