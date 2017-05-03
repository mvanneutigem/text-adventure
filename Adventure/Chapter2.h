#pragma once
#include "State.h"

class Chapter2 : public State
{
public:
	Chapter2();
	~Chapter2();

	void Enter() override;
	void Update(FileReader m_Reader) override;
	void Exit() override;

private:
	bool m_LookedAtDesk = false;
	bool m_FoundBloodstain = false;
	bool m_InspectedCouch = false;
	bool m_FoundLetter = false;
	bool m_TalkedToNeighbour = false;
	bool m_TalkedToSilver = false;
	bool m_ReceivedCall = false;
};
