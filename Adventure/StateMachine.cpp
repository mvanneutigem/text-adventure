#include "StateMachine.h"
#include "Chapter1.h"

StateMachine::StateMachine()
{
}


StateMachine::~StateMachine()
{
}

void StateMachine::ChangeState(State* s)
{
	if(m_State)
	{
		m_State->Exit();
	}
	m_State = s;
	m_State->Enter();
}

State* StateMachine::GetCurrentState() const
{
	return m_State;
}
