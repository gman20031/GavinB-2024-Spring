#include "Deck.h"

#include <random>

Deck::Deck()
	: m_pAllCards{nullptr}
	, m_drawPileSize{0}
	, m_pDrawPile{nullptr}
	, m_discardPileSize{0}
	, m_pDiscardPile{nullptr}
{
	CreateCards();
	for (int i = 0; i < kNumFaceValues * kCardNumSuits; ++i)
	{
		AddToDrawPile(m_pAllCards[i]);
	}
}

Deck::~Deck()
{
	for (size_t i = 0; i < kNumFaceValues * kCardNumSuits; ++i)
	{
		delete m_pAllCards[i];
	}
}

/////////////////////////////////////////////////////////////////
// Creates the unique cards in a standard deck.
/////////////////////////////////////////////////////////////////
void Deck::CreateCards()
{
	size_t index = 0;
	for (size_t face = 0; face < kNumFaceValues; ++face)
	{
		for (size_t suit = 0; suit < kCardNumSuits; ++suit)
		{
			m_pAllCards[index] = new Card{ static_cast<Card::FaceNames>(face + 1),
											static_cast<Card::SuitNames>(suit) };

			++index;	// move to next card
		}
	}
}

/////////////////////////////////////////////////////////////////
// Adds the given pCard to the given ppPile.
// pileSize is needed to know where the card
// belongs; it will be incremented.
/////////////////////////////////////////////////////////////////
void Deck::AddCardToPile(Card* const pCard, cardpile ppPile, size_t& pileSize) const
{
	ppPile[pileSize] = pCard;
	++pileSize;
}

/////////////////////////////////////////////////////////////////
// Randomizes the order of elements in ppPile.
/////////////////////////////////////////////////////////////////
void Deck::Shuffle(cardpile const ppPile, const size_t pileSize) const
{
	// Simple Fisher-Yates shuffle
	// We swap each card with some other randomly picked card.
	for (size_t i = 0; i < pileSize; ++i)
	{
		// Pick another random card
		// As i increases, we will exclude cards we already swapped
		size_t randomIndex = i + rand() % (pileSize - i);

		// Do a simple swap of the two card pointers
		Card* pTemp = ppPile[i];
		ppPile[i] = ppPile[randomIndex];
		ppPile[randomIndex] = pTemp;
	}
}

/////////////////////////////////////////////////////////////////
// Draws a card from ppPile. pileSize is needed
// to know where the card is; it will be
// decremented.
/////////////////////////////////////////////////////////////////
Card* Deck::DrawCard(cardpile const ppPile, size_t& pileSize) const
{
	if (pileSize == 0)
		return nullptr;

	--pileSize;
	return ppPile[pileSize];
}
