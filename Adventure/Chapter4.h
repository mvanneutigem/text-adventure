#pragma once
#include "State.h"

class Chapter4 : public State
{
public:
	Chapter4();
	~Chapter4();

	void Enter() override;
	void Update(FileReader& m_Reader) override;
	void Exit() override;

	bool m_gotCarlysCall = false;
	bool m_CarlyConfessed = false;
	bool m_accusedGeoffrey = false;
	bool m_GotAutopsy = false;
};

