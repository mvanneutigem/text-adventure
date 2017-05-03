#pragma once
#include "State.h"
class StateMachine
{
public:

	StateMachine();
	~StateMachine();

	void ChangeState(State* s);
	State* GetCurrentState() const;

private:
	State* m_State = nullptr;

};

