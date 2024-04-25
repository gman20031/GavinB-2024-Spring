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

	m_pArray = new ArrayType[startSize];
	SetValues(startValue);
}

template<typename ArrayType>
constexpr DynamicArray<ArrayType>::DynamicArray(size_t startSize)
	: DynamicArray<ArrayType>(startSize, kDefaultVal)
{
}

template<typename ArrayType>
DynamicArray<ArrayType>::DynamicArray()
	: DynamicArray<ArrayType>(0 , kDefaultVal)
{
}

// Sets all allocated elements equal to value
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::SetValues(ArrayType value)
{
	if (m_size == 0)
		return;
	for (size_t i = 0; i < m_capacity ; ++i)
	{
		m_pArray[i] = value;
	}
}

// Increases m_size by count
// reallocated array at 2 * capacity if required
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::AddElements(size_t count)
{
	m_size += count;
	if (m_size > m_capacity)
		Resize(m_capacity * 2);
}

// allocates count number of elements at pos growing right
// all elements at those locations are shifted right
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::AllocateElements(ConstIterator pos, size_t count)
{
	AddElements(count);
	for (Iterator it = end() - 1; it != (pos + count - 1); --it)
	{
		*(it) = *(it - count);
	}
	for (Iterator it = pos; it != (pos + count - 1); ++it)
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
		SetValues(kDefaultVal);
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


////////////////////////////// Deletion //////////////////////////////

template<typename ArrayType>
constexpr DynamicArray<ArrayType>::~DynamicArray()
{
	delete[] m_pArray;
}



////////////////////////////// assignment //////////////////////////////

// replaces array with count copies of value
template<typename ArrayType>
DynamicArray<ArrayType>* DynamicArray<ArrayType>::assign(size_t count, const ArrayType& value)
{
	return nullptr;
}

// Sets the array to iList
template<typename ArrayType>
DynamicArray<ArrayType>* DynamicArray<ArrayType>::assign(std::initializer_list<ArrayType> iList)
{
	return nullptr;
}

// replaces array contents with copiedArray
template<typename ArrayType>
DynamicArray<ArrayType>* DynamicArray<ArrayType>::operator=(DynamicArray& copiedArray)
{
	return nullptr;
}

////////////////////////////// comparison //////////////////////////////

template<typename ArrayType>
bool DynamicArray<ArrayType>::operator==(const DynamicArray<ArrayType>& rhs)
{
	if (m_size != rhs.m_size)
		return false;

	for (size_t i = 0; i < m_size; ++i)
	{
		if (m_pArray[i] != rhs.m_pArray[i])
			return false;
	}

	return true;
}

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
void DynamicArray<ArrayType>::Clear()
{
}

// Push's value to back of array
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::PushBack(const ArrayType& newElement)
{
}

// Insert value at position indicated, shifting array right to fit
template<typename ArrayType>
constexpr DynamicArray<ArrayType> ::Iterator DynamicArray<ArrayType>::Add(const ArrayType& newElement, size_t index)
{
}

// Insert value at position indicated, shifting array right to fit
template<typename ArrayType>
constexpr DynamicArray<ArrayType> ::Iterator DynamicArray<ArrayType>::Add(const ArrayType& newElement, DynamicArray::ConstIterator pos)
{
}

// Insert value at position indicated, shifting array right to fit
template<typename ArrayType>
constexpr DynamicArray<ArrayType>::Iterator DynamicArray<ArrayType>::Add(ArrayType&& newElement, DynamicArray::ConstIterator pos)
{
}

// insert a range of values at pos, shifting elements right to fit
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::InsertRange(const std::list<ArrayType>& range, ConstIterator pos)
{
	size_t shiftCount = range.size();

	for (const ArrayType& value : range)
	{

	}
}

// Appends range of values to the end of array
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::AppendRange(const std::list<ArrayType>& range)
{
}

// replaces the value at index with 0, shifts the array to the left to fill in
// reduces size
template<typename ArrayType>
void DynamicArray<ArrayType>::Erase(size_t index)
{

}

// Erases the last element of the array
// reduces size
template<typename ArrayType>
void DynamicArray<ArrayType>::PopBack()
{
	Erase(m_size - 1);
}

// Reallocated the array to newCapacity 
template<typename ArrayType>
bool DynamicArray<ArrayType>::Resize(size_t newCapacity)
{
	if (newCapacity == m_capacity)
		return;

	ArrayType* newArray = new ArrayType[newCapacity];

	for (size_t i = 0; i < m_size; ++i)
	{
		newArray[i] = m_pArray[i];
	}

	delete[] m_pArray;
	m_pArray = newArray;
}

// Swaps the values at two indecies
template<typename ArrayType>
void DynamicArray<ArrayType>::Swap(size_t indexOne, size_t indexTwo)
{
	ConstIterator posOne = &m_pArray[indexOne];
	ConstIterator posTwo = &m_pArray[indexTwo];
	Swap(posOne, posTwo);
}

// Swaps the values pointed to by two iterators
template<typename ArrayType>
void DynamicArray<ArrayType>::Swap(ConstIterator posOne, ConstIterator posTwo)
{
	ArrayType temp = *posOne;
	*posOne = *posTwo;
	*posTwo = temp;
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
	Resize(m_size);
	return true;
}

// if newCapacity <= capacity this does nothing
// otherwise calls Resize(newCapacity)
template<typename ArrayType>
constexpr void DynamicArray<ArrayType>::Reserve(size_t newCapacity)
{
	if (newCapacity <= m_capacity)
		return;
	Resize(newCapacity);
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
