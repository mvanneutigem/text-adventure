#pragma once
class FileReader;

class State
{
public:
	State(){}
	virtual ~State(){}

	virtual void Enter() = 0;
	virtual void Update(FileReader& m_Reader) = 0;
	virtual void Exit() = 0;
};

