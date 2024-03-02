#include "Card.h"

const std::string Card::s_faceNames[] = {
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

const std::string Card::s_suitNames[] = {
	"Clubs",
	"Diamonds",
	"Hearts",
	"Spades"
};


/////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////
Card::Card(FaceNames face, SuitNames suit)
	: m_face{ face }
	, m_suit{ suit }
{}

/////////////////////////////////////////////////////////////////
// Returns this card's name in the form "(FaceValue) of (Suit)s"
/////////////////////////////////////////////////////////////////
std::string Card::GetName() const
{
	return GetFaceName(m_face) + " of " + GetSuitName(m_suit);
}

//////////////////////////////////////////////////////////////////////////////
// Returns string in the form "(FaceValue) of (Suit)s" given a face and suit  
//////////////////////////////////////////////////////////////////////////////
std::string Card::GetName(FaceNames face, SuitNames suit) 
{
	return GetFaceName(face) + " of " + GetSuitName(suit);
}

/////////////////////////////////////////////////////////////////
// Converts this card's face value to a word from m_faceNames.
/////////////////////////////////////////////////////////////////
std::string Card::GetFaceName(FaceNames face)
{
	return s_faceNames[static_cast<size_t>(face) - 1];
}

/////////////////////////////////////////////////////////////////
// Converts this card's suit value to a word from m_suitNames.
/////////////////////////////////////////////////////////////////
std::string Card::GetSuitName(SuitNames suit)
{
	return s_suitNames[static_cast<size_t>(suit)];
}

