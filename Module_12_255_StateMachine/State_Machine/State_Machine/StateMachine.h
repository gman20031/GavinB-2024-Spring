#pragma once

#include <assert.h>
#include <concepts>
#include <memory>

#include "State.h"


template<subState State_t>
class StateMachine
{
protected:
	State_t* m_pState = nullptr;
public:

	void ChangeState(State_t* pNewState)
	{
		assert(pNewState != nullptr);
		if (m_pState)
			m_pState->OnExit();
		delete m_pState;
		m_pState = pNewState;
		m_pState->OnEnter();
	}
};