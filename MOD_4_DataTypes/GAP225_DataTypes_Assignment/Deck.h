#pragma once

#include <assert.h>
#include <string>

#include "Card.h"

using cardpile = Card**;
#define kCardNumSuits Card::kNumSuits
#define kNumFaceValues Card::kNumFaceValues

/////////////////////////////////////////////////////////////////
// A standard playing card deck implementation.
/////////////////////////////////////////////////////////////////
class Deck
{
public:
	static constexpr size_t maxDeckSize = kNumFaceValues * kCardNumSuits;
private:
	// All cards are stored here, regardless of where they are
	Card* m_pAllCards[maxDeckSize];

	// Draw pile
	size_t m_drawPileSize;
	Card*  m_pDrawPile[maxDeckSize];

	// Discard pile
	size_t m_discardPileSize;
	Card* m_pDiscardPile[maxDeckSize];

	void CreateCards();

	// im unsure on the Constness of these functions, they technically can be const because
	// THEY dont change any member variables, but then 
	void AddCardToPile(Card* const pCard, cardpile ppPile, size_t& pileSize) const ;
	void Shuffle(cardpile const ppPile, const size_t pileSize) const ;
	Card* DrawCard(cardpile const ppPile, size_t& pileSize) const ;
	 
public:
	Deck();
	~Deck();

	// Place a card on top of the main pile.
	void AddToDrawPile(Card* pCard) { AddCardToPile(pCard, m_pDrawPile, m_drawPileSize); }

	// Shuffle the main pile.
	void ShuffleDrawPile() { Shuffle(m_pDrawPile, m_drawPileSize); }

	// Draw from the main pile.
	Card* DrawFromDrawPile() { return DrawCard(m_pDrawPile, m_drawPileSize); }

	// Place a card on top of the discard pile.
	void AddToDiscardPile(Card* pCard) { AddCardToPile(pCard, m_pDiscardPile, m_discardPileSize); }
	
	// Shuffle the discard pile.
	void ShuffleDiscardPile() { Shuffle(m_pDiscardPile, m_discardPileSize); }
	
	// Draw from the discard pile.
	Card* DrawFromDiscardPile() { return DrawCard(m_pDiscardPile, m_discardPileSize); }
};

