#include "StateMachine.h"
#include "Chapter1.h"

StateMachine::StateMachine()
{
}


StateMachine::~StateMachine()
{
	//delete m_State;
	//m_State = nullptr;
}

void StateMachine::ChangeState(State* s)
{
	if(m_State)
	{
		m_State->Exit();
	}

	s->Enter();
	m_State = s;
}

State* StateMachine::GetCurrentState() const
{
	return m_State;
}
