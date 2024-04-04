#pragma once
#pragma once

#include <iterator>
#include <string>

// THIS IS SOMETHING, PLEASE DONT WORRY ABOUT IT RIGHT NOW


//using Type = int;
template <typename Type>
class TwoDimensionalArray
{
public:
	Type* const operator[](size_t index) { return m_ppArray[index]; }
	const Type* const operator[](size_t index) const { return m_ppArray[index]; }


	Type* const operator*() { return *m_ppArray; }
	Type*** operator&() { return &m_ppArray; }


private:
	Type** m_ppArray;
	Type* m_pStart;
	Type* m_pEnd;

	size_t m_collumnLength;
	size_t m_rowLength;
	size_t m_size;

	inline static size_t s_count = 0;

	void DeleteMemory()
	{
		// I only technically call New twice as the 0th element of the array is the only time i ask for space.
				// Unsure how New works under the hood to know this, but this should be fine
		delete[] * m_ppArray;
		delete[] m_ppArray;
	}

#if DEBUG_ARRAY
	void TwoDimensionalArray::DebugPrint()
	{
		std::cout << "Debug Print: \n"
			<< "m_ppArray: " << m_ppArray << '\n'
			<< "m_ppStart: " << m_pStart << '\n'
			<< "m_ppEnd: " << m_pEnd << '\n'
			<< "m_collumnLength: " << m_collumnLength << '\n'
			<< "m_rowLength: " << m_rowLength << '\n'
			<< "m_size: " << m_size << '\n'
			<< "Count: " << s_count << '\n'
			<< "contents : \n";
		for (auto& contents : *this)
		{
			std::cout << contents << " , ";
		}
		std::cout << "\n";
	}
#endif // DEBUG_ARRAY

public:
	TwoDimensionalArray(size_t collumnLength, size_t rowLength)
		: m_size(rowLength* collumnLength)
		, m_ppArray(nullptr)
	{
		++s_count;
		Resize(collumnLength, rowLength);
	}
	TwoDimensionalArray()
		:TwoDimensionalArray(0, 0) {}
	TwoDimensionalArray(const TwoDimensionalArray& original)
		: m_rowLength(original.m_rowLength)
		, m_collumnLength(original.m_collumnLength)
		, m_size(original.m_size)
		, m_ppArray(original.m_ppArray)
		, m_pStart(original.m_pStart)
		, m_pEnd(original.m_pEnd)
	{
		++s_count;
	}
	~TwoDimensionalArray()
	{
		--s_count;
		if (s_count == 0)
			DeleteMemory();
	}

	void Resize(size_t collumnLength, size_t rowLength)
	{
		if (m_size != 0)
			DeleteMemory();

		m_rowLength = rowLength;
		m_collumnLength = collumnLength;
		m_size = rowLength * collumnLength;

		//Creates a contiguous block of memory for the whole two D array.
		m_ppArray = new Type * [m_collumnLength];// Creates a block of memory for the pointers
		m_ppArray[0] = new Type[m_size];		 // creates a contiguos block of memory for all data
		if (m_collumnLength > 1)
		{
			for (size_t i = 1; i < m_collumnLength; ++i)
			{
				// Gives the pointers the start adress of their 'row'
				m_ppArray[i] = m_ppArray[i - 1] + m_rowLength;
			}
		}
		m_pStart = m_ppArray[0];
		m_pEnd = &m_ppArray[0][m_size];
	}

	class TwoDimensionalArrayIterator
	{
	public:
		using iterator = TwoDimensionalArrayIterator;
		using iteratorCategory = std::contiguous_iterator_tag;
		using differenceType = std::ptrdiff_t;
		using ItDataType = Type;
		using ItPointer = ItDataType*;
		using ItReference = ItDataType&;
		ItReference operator*() const { return *m_pointer; }
		ItPointer operator ->() { return m_pointer; }

		iterator& operator++() {
			++m_pointer;
			return *this;
		}
		iterator operator++(int) {
			iterator before = *this;
			++(*this);
			return before;
		}
		iterator& operator--() {
			--m_pointer;
			return *this;
		}
		iterator operator--(int) {
			iterator before = *this;
			--(*this);
			return before;
		}
		bool operator==(const iterator& rhs) { return (this->m_pointer == rhs.m_pointer); }
		bool operator!=(const iterator& rhs) { return (this->m_pointer != rhs.m_pointer); }
	private:
		ItPointer m_pointer;

	public:
		TwoDimensionalArrayIterator(ItPointer pointer)
			: m_pointer(pointer) {};
	};

	TwoDimensionalArrayIterator begin()
	{
		return TwoDimensionalArrayIterator(m_pStart);
	}
	TwoDimensionalArrayIterator end()
	{
		return TwoDimensionalArrayIterator(m_pEnd);
	}


	class Const_TwoDimensionalArrayIterator
	{
	public:
		using iterator = Const_TwoDimensionalArrayIterator;
		using iteratorCategory = std::contiguous_iterator_tag;
		using differenceType = std::ptrdiff_t;
		using ItDataType = const Type;
		using ItPointer = ItDataType*;
		using ItReference = ItDataType&;

		const ItReference operator*() const { return *m_pointer; }
		const ItPointer operator ->() { return m_pointer; }

		iterator& operator++()
		{
			++m_pointer;
			return *this;
		}
		iterator operator++(int)
		{
			iterator before = *this;
			++(*this);
			return before;
		}
		iterator& operator--()
		{
			--m_pointer;
			return *this;
		}
		iterator operator--(int)
		{
			iterator before = *this;
			--(*this);
			return before;
		}
		bool operator==(const iterator& rhs) { return (this->m_pointer == rhs.m_pointer); }
		bool operator!=(const iterator& rhs) { return (this->m_pointer != rhs.m_pointer); }
	private:
		ItPointer m_pointer;

	public:
		Const_TwoDimensionalArrayIterator(ItPointer  pointer)
			: m_pointer(pointer) {};
	};

	Const_TwoDimensionalArrayIterator begin() const
	{
		return Const_TwoDimensionalArrayIterator(m_pStart);
	}
	Const_TwoDimensionalArrayIterator end() const
	{
		return Const_TwoDimensionalArrayIterator(m_pEnd);
	}
};
