#pragma once
#include <concepts>



class State
{
public:
	virtual ~State() = default;
	virtual void OnEnter() = 0;
	virtual void OnExit()  = 0;
};

template<typename T>
concept subState = std::derived_from<T, State>;