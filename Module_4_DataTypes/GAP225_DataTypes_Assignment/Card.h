#pragma once

#include <assert.h>
#include <string>

class Card
{
public:
	enum class FaceNames
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

	enum class SuitNames
	{
		kClubs,
		kDiamonds,
		kHearts,
		kSpades,
	};

	static constexpr size_t kNumFaceValues = 13;	// There are 13 unique card values, including Ace, Jack, Queen, King
	static constexpr size_t kNumSuits = 4;			// There are 4 suit
private:
	FaceNames m_face;
	SuitNames m_suit;

	static const std::string s_faceNames[kNumFaceValues];
	static const std::string s_suitNames[kNumSuits];
public:
	Card(FaceNames face, SuitNames suit);


	FaceNames GetFaceValue() const { return m_face; }
	SuitNames GetSuit() const { return m_suit; }
	std::string GetName() const;

	static std::string GetName(FaceNames face, SuitNames suit);
private:
	static std::string GetFaceName(FaceNames face);
	static std::string GetSuitName(SuitNames suit);
};

