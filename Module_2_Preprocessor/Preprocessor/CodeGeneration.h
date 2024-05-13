#pragma once

#define PRIVATE_VARIABLE_WITH_PUBLIC_GETTER_AND_SETTER(type,id)\
	private:													\
		type m_##id = 0;										\
	public:														\
		type Get##id()											\
		{														\
			return m_##id;										\
		}														\
		void Set##id(type new##id)								\
		{														\
			m_##id = new##id;									\
		}														\
																    