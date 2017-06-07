#pragma once
#include "State.h"

class FileReader;

class Chapter1 : public State
{
public:
	Chapter1();
	~Chapter1();

	void Enter() override;
	void Update(FileReader& m_Reader) override;
	void Exit() override;

private:
	bool m_EnteredCrimeScene = false;
	bool m_gotPreliminaryReport = false;
	bool m_SeenMachine = false;
	bool m_CollectedEvidence01 = false;
	bool m_CollectedEvidence02 = false;
	bool m_CollectedEvidence03 = false;
};

