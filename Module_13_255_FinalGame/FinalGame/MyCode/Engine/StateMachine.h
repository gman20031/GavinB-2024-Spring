#pragma once

#include <concepts>

class State
{
public:
	virtual ~State() = default;
	virtual void OnEnter() {};
	virtual void OnExit() {};
};

template<typename T>
concept subState = std::derived_from<T, State>;

template<subState State_t>
class StateMachine
{
protected:
	State_t* m_pState = nullptr;
public:
	~StateMachine() { delete m_pState; }

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