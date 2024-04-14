#pragma once

#if TEST_ARRAY
#include "Test.h"
#endif

#include <list>

template<typename ArrayType>
class DynamicArray
{
	static constexpr int kDefaultVal = 0;
	using TypePtr = ArrayType*;
	using Iterator = TypePtr;
	using ConstIterator = ArrayType* const;
	using ConstPtr = const TypePtr;

	size_t m_size;
	size_t m_capacity;

	ArrayType* m_pArray;

	// helpers
	constexpr void Reallocate(size_t newCapacity);
	constexpr bool AddElements(size_t count = 0);
	constexpr void SetValueToCapacity(ArrayType value);
	constexpr void SetValueToSize(ArrayType value);
	constexpr void InsertElements(ConstIterator pos, size_t count = 1);
	constexpr void RemoveElements(ConstIterator pos, size_t count = 1);

public:
	DynamicArray();
	constexpr DynamicArray(size_t startSize);
	constexpr DynamicArray(size_t startSize, ArrayType startValue);
	constexpr DynamicArray(const DynamicArray& original);
	constexpr ~DynamicArray();

	// assignment 
	constexpr void assign(size_t count, const ArrayType& value);
	constexpr void assign(std::initializer_list<ArrayType> iList);

	DynamicArray<ArrayType>& operator=(const DynamicArray<ArrayType>& copiedArray);
	DynamicArray<ArrayType>& operator=(std::initializer_list<ArrayType> iList);

	// comparison
	template<typename TypeA, typename TypeB>
	friend bool operator==(const DynamicArray<TypeA>& lhs , const DynamicArray<TypeB>& rhs);

	// element access 
	ArrayType& Get(size_t index);
	ArrayType& operator[](size_t index);
	ArrayType& Front() { return m_pArray[0]; };
	ArrayType& Back()  { return m_pArray[m_size - 1]; }
	TypePtr Data() { return m_pArray; }

	// modifiers
	constexpr void Clear(); // deletes contents
	constexpr void PushBack(const ArrayType& newElement); // push back
	constexpr Iterator Add(const ArrayType& newElement, size_t index); //insert
	constexpr Iterator Add(const ArrayType& newElement, ConstIterator pos); //insert
	constexpr DynamicArray& operator+=(const ArrayType& newElement);
	constexpr void InsertRange(const std::list<ArrayType>& range, ConstIterator pos);
	constexpr void AppendRange(const std::list<ArrayType>& range); 
	constexpr void Erase(size_t index); // remove
	constexpr DynamicArray& operator-=(size_t index);
	constexpr void PopBack();
	constexpr void Resize(size_t newSize);
	constexpr void Swap(size_t indexOne, size_t indexTwo);
	constexpr void Swap(ConstIterator posOne, ConstIterator posTwo);

	// capacity
	bool Empty() { return (m_size == 0); } // checks whether the container is empty 
	size_t GetSize() { return m_size; } // Returns number of elements
	size_t GetCapacity() { return m_capacity; } // returns allocated space
	size_t MaxSize();
	constexpr bool ShrinkToFit();
	constexpr void Reserve(size_t newCapacity);

	// iterator
	Iterator begin() { return m_pArray; }
	Iterator end() { return &m_pArray[m_size]; }
};

#include "DynamicArray.h"

#include <limits>
#include <compare>

////////////////////////////// initialization //////////////////////////////
template<typename ArrayType>
constexpr DynamicArray<ArrayType>::DynamicArray(size_t startSize, ArrayType startValue)
{
	if (startSize == 0)
		m_capacity = 1;
	else
		m_capacity = startSize;

	startValue == kDefaultVal ? m_size = 0 : m_size = startSize;

	m_pArray = new ArrayType[m_capacity];
	SetValueToCapacity(startValue);
}

template<typename ArrayType>
constexpr DynamicArray<ArrayType>::DynamicArray(size_t startSize)
	: DynamicArray<ArrayType>(startSize, kDefaultVal)
{
}

template<typename ArrayType>
DynamicArray<ArrayType>::DynamicArray()
	: DynamicArray<ArrayType>(0, kDefaultVal)
{
}

template<typename ArrayType>
inline constexpr DynamicArray<ArrayType>::DynamicArray(const DynamicArray& original)
	: m_size(original.m_size)
	, m_capacity(original.m_size)
	, m_pArray(nullptr)
{
	*this = original;
}

////////////////////////////// Deletion //////////////////////////////

template<typename ArrayType>
constexpr DynamicArray<ArrayType>::~DynamicArray()
{
	if(m_pArray)
		delete[] m_pArray;
}

////////////////////////////// Helpers //////////////////////////////

// Reallocated the array to newCapacity 
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::Reallocate(size_t newCapacity)
{
	m_capacity = newCapacity;
	ArrayType* newArray = new ArrayType[newCapacity];

	for (size_t i = 0; i < m_size; ++i)
	{
		newArray[i] = m_pArray[i];
	}

	delete[] m_pArray;
	m_pArray = newArray;
}

// Increases m_size by count
// reallocated array at 2 * capacity if required
// returns true of array was reallocated
template<typename ArrayType>
constexpr bool DynamicArray<ArrayType>::AddElements(size_t count)
{
	bool resized = false;
	m_size += count;
	while (m_size > m_capacity)
	{
		Reallocate(m_capacity * 2);
		resized = true;
	}
	return resized;
}

// Sets all allocated space equal to value
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::SetValueToCapacity(ArrayType value)
{
	for (size_t i = 0; i < m_capacity; ++i)
	{
		m_pArray[i] = value;
	}
}

// Sets all values upto m_size to value
template<typename ArrayType>
inline constexpr void DynamicArray<ArrayType>::SetValueToSize(ArrayType value)
{
	for (ArrayType& object : *this)
	{
		object = value;
	}
}

// inserts count number of elements at pos growing right
// all elements at those locations are shifted right to make room
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::InsertElements(ConstIterator pos, size_t count)
{
	size_t index = pos - begin();
	Iterator newPos = pos;

	if (AddElements(count))
		newPos = begin() + index;

	for (Iterator it = end() - 1; it != (newPos + count - 1); --it)
	{
		*(it) = *(it - count);
	}
	for (Iterator it = newPos; it != (newPos + count); ++it)
	{
		*it = kDefaultVal;
	}
}

// Reduces size by count
// then shifts everything shifts everything to the right of pos+count left until pos
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::RemoveElements(ConstIterator pos, size_t count)
{
	m_size -= count;
	if (m_size <= 0)
		SetValueToCapacity(kDefaultVal);
	else
	{
		ConstIterator& endIt = end();
		for (Iterator it = pos; it != endIt; ++it)
		{
			if ((it + count) >= endIt)
				*it = kDefaultVal;
			else
				*it = *(it + count);
		}
	}
}


////////////////////////////// assignment //////////////////////////////

// replaces array with count copies of value
template<typename ArrayType>
constexpr void  DynamicArray<ArrayType>::assign(size_t count, const ArrayType& value)
{
	m_size = count;
	if (m_size > m_capacity)
		AddElements();
	SetValueToSize(value);
}

// Sets the array to iList
template<typename ArrayType>
constexpr void  DynamicArray<ArrayType>::assign(std::initializer_list<ArrayType> iList)
{
	m_size = iList.size();
	if (m_size > m_capacity)
		AddElements();
	size_t i = 0;
	for (const ArrayType& object : iList)
	{
		m_pArray[i] = object;
		++i;
	}
}

// replaces array contents with copiedArray
template<typename ArrayType>
DynamicArray<ArrayType>& DynamicArray<ArrayType>::operator=(const DynamicArray<ArrayType>& copiedArray)
{
	if (*this == copiedArray)
		return *this;

	m_size = copiedArray.m_size;
	m_capacity = copiedArray.m_capacity;
	Reallocate(m_capacity);
	SetValueToCapacity(kDefaultVal);
	for(size_t i = 0; i < m_size; ++i)
	{
		m_pArray[i] = copiedArray.m_pArray[i];
	}
	return *this;
}

template<typename ArrayType>
inline DynamicArray<ArrayType>& DynamicArray<ArrayType>::operator=(std::initializer_list<ArrayType> iList)
{
	assign(iList);
	return *this;
}


////////////////////////////// comparison //////////////////////////////

template<typename TypeA, typename TypeB>
bool operator==(const DynamicArray<TypeA>& lhs, const DynamicArray<TypeB>& rhs)
{
	if (lhs.m_size != rhs.m_size)
		return false;

	for (size_t i = 0; i < lhs.m_size; ++i)
	{
		if (lhs.m_pArray[i] != rhs.m_pArray[i])
			return false;
	}

	return true;
}

template<typename TypeA, typename TypeB>
bool operator!=(const DynamicArray<TypeA>& lhs, const DynamicArray<TypeB>& rhs)
{
	return !(lhs == rhs);
}

//template<typename TypeA, typename TypeB>
//auto operator<=>(const DynamicArray<TypeA>& lhs, const DynamicArray<TypeB>& rhs) = default;

////////////////////////////// element access //////////////////////////////

// returns refference to element at index
template<typename ArrayType>
ArrayType& DynamicArray<ArrayType>::Get(size_t index)
{
	return m_pArray[index];
}

// returns refference to element at index
template<typename ArrayType>
ArrayType& DynamicArray<ArrayType>::operator[](size_t index)
{
	return Get(index);
}



////////////////////////////// modifiers //////////////////////////////

// replaces all elements of array with 0
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::Clear()
{
	m_size = 0;
	SetValueToCapacity(kDefaultVal);
}

// Push's value to back of array
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::PushBack(const ArrayType& newElement)
{
	AddElements(1);
	Back() = newElement;
}

// Calls PushBack(newElement)
template<typename ArrayType>
inline constexpr DynamicArray<ArrayType>& DynamicArray<ArrayType>::operator+=(const ArrayType& newElement)
{
	PushBack(newElement);
	return *this;
}

// Insert value at position indicated, shifting array right to fit
template<typename ArrayType>
constexpr DynamicArray<ArrayType> ::Iterator DynamicArray<ArrayType>::Add(const ArrayType& newElement, DynamicArray::ConstIterator pos)
{
	InsertElements(pos);
	*pos = newElement;
	return pos;
}

// Insert value at position indicated, shifting array right to fit
template<typename ArrayType>
constexpr DynamicArray<ArrayType> ::Iterator DynamicArray<ArrayType>::Add(const ArrayType& newElement, size_t index)
{
	return Add(newElement, begin() + 1);
}

// insert a range of values at pos, shifting elements right to fit
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::InsertRange(const std::list<ArrayType>& range, ConstIterator pos)
{
	size_t index = pos - begin();
	InsertElements(pos, range.size());

	Iterator it = begin() + index;
	for (const ArrayType& object : range)
	{
		*it = object;
		++it;
	}
}

// Appends range of values to the end of array
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::AppendRange(const std::list<ArrayType>& range)
{
	AddElements(range.size());
	Iterator it = (end() - range.size());
	for (const ArrayType& object : range)
	{
		*it = object;
		++it;
	}
}

// replaces the value at index with 0, shifts the array to the left to fill in
// reduces size
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::Erase(size_t index)
{
	RemoveElements(begin() + index);
}

template<typename ArrayType>
constexpr DynamicArray<ArrayType>& DynamicArray<ArrayType>::operator-=(size_t index)
{
	Erase(index);
	return *this;
}

// Erases the last element of the array
// reduces size
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::PopBack()
{
	Erase(m_size - 1);
}

template<typename ArrayType>
inline constexpr void DynamicArray<ArrayType>::Resize(size_t newSize)
{
	if (newSize < m_capacity)
		m_size = newSize;
	Reallocate(newSize);
}

// Swaps the values pointed to by two iterators
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::Swap(ConstIterator posOne, ConstIterator posTwo)
{
	ArrayType temp = *posOne;
	*posOne = *posTwo;
	*posTwo = temp;
}

// Swaps the values at two indecies
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::Swap(size_t indexOne, size_t indexTwo)
{
	Swap(begin() + indexOne, begin() + indexTwo);
}

////////////////////////////// capactity //////////////////////////////

// returns the maximum possible elements the array can contain
template<typename ArrayType>
size_t DynamicArray<ArrayType>::MaxSize()
{
	return std::numeric_limits<size_t>::max();
}

// shrinks the capacity of this array to match the size
template<typename ArrayType>
constexpr bool DynamicArray<ArrayType>::ShrinkToFit()
{
	Reallocate(m_size);
	return true;
}

// if newCapacity <= capacity this does nothing
// otherwise calls Resize(newCapacity)
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::Reserve(size_t newCapacity)
{
	if (newCapacity <= m_capacity)
		return;
	Reallocate(newCapacity);
}

////////////////////////////// iterator //////////////////////////////

//template<typename ArrayType>
//DynamicArray<ArrayType>::Iterator DynamicArray<ArrayType>::begin()
//{
//	return Iterator();
//}
//
//template<typename ArrayType>
//DynamicArray<ArrayType>::Iterator DynamicArray<ArrayType>::end()
//{
//	return Iterator();
//}


