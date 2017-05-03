#pragma once
#include "State.h"

class Chapter3 : public State
{
public:
	Chapter3();
	~Chapter3();

	void Enter() override;
	void Update(FileReader m_Reader) override;
	void Exit() override;
};

