#pragma once
#include <iostream>
#include <concepts>

template<typename Type>
class Toggle
{
	Type m_firstValue;
	Type m_secondValue;
	bool m_toggled = true;
public:
	Toggle(Type val1, Type val2) : m_firstValue(val1), m_secondValue(val2) {}
	Type Get();
	void ToggleValue();
};

template<typename Type>
inline Type Toggle<Type>::Get()
{
	Type Val = {};
	m_toggled ? Val =  m_firstValue : Val = m_secondValue;
	return Val;
}

template<typename Type>
inline void Toggle<Type>::ToggleValue()
{
	m_toggled ? m_toggled = false : m_toggled = true;
}

