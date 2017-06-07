#pragma once
#include "State.h"

class Chapter3 : public State
{
public:
	Chapter3();
	~Chapter3();

	void Enter() override;
	void Update(FileReader& m_Reader) override;
	void Exit() override;

	bool m_LookedAtDesk = false;
	bool m_CheckedDrawers = false;
	bool m_FoundRouter = false;
	bool m_FoundPowder = false;

	bool m_receivedCall = false;
	bool m_DecodeFootage = false;
	bool m_ReceivedCallFromBoss = false;
	bool m_ConfrontedOliver = false;

};

