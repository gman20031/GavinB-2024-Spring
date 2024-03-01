#pragma once

#include <assert.h>
#include <string>

class Card
{
public:
	static constexpr size_t kNumFaceValues = 13;	// There are 13 unique card values, including Ace, Jack, Queen, King
	static constexpr size_t kNumSuits = 4;			// There are 4 suits

private:
	size_t m_faceValue;
	size_t m_suit;

	enum class faceNames
	{
		kAce = 1,
		kTwo,
		kThree,
		kFour,
		kFive,
		kSix,
		kSeven,
		kEight,
		kNine,
		kTen,
		kJack,
		kQueen,
		kKing = 13,
	};
	std::string m_faceNames[kNumFaceValues]{
		"Ace",
		"Two",
		"Three",
		"Four",
		"Five",
		"Six",
		"Seven",
		"Eight",
		"Nine",
		"Ten",
		"Jack",
		"Queen",
		"King"
	};

	enum class SuitNames
	{
		kClubs,
		kDiamonds,
		kHearts,
		kSpades,
	};
	std::string m_suitNames[kNumSuits]{ 
		"Clubs",
		"Diamonds",
		"Hearts",
		"Spades" 
	};

public:
	Card(int faceValue, int suit)
		: m_faceValue{ faceValue }
		, m_suit{ suit }
	{
		assert(faceValue >= kMinFaceValue && faceValue <= kMaxFaceValue);
		assert(suit >= kMinSuitValue && suit <= kMaxFaceValue);
	}

	int GetFaceValue() const { return m_faceValue; }
	int GetSuit() const { return m_suit; }

	/////////////////////////////////////////////////////////////////
	// Returns this card's name in the form "(FaceValue) of (Suit)s"
	/////////////////////////////////////////////////////////////////
	std::string GetName()
	{
		return GetFaceName() + " of " + GetSuitName();
	}

private:
	/////////////////////////////////////////////////////////////////
	// Converts this card's face value to a word from m_faceNames.
	/////////////////////////////////////////////////////////////////
	std::string GetFaceName()
	{
		return m_faceNames[m_faceValue - 1];
	}

	/////////////////////////////////////////////////////////////////
	// Converts this card's suit value to a word from m_suitNames.
	/////////////////////////////////////////////////////////////////
	std::string GetSuitName()
	{
		return m_suitNames[m_suit];
	}
};