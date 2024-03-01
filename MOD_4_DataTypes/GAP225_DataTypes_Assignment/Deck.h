#pragma once

#include <assert.h>
#include <string>

#include "Card.h"
//using uShort = unsigned short;
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
	int m_drawPileSize;
	Card* m_pDrawPile[maxDeckSize];

	// Discard pile
	int m_discardPileSize;
	Card* m_pDiscardPile[maxDeckSize];

	void CreateCards();
	void AddCardToPile(Card* pCard, Card** ppPile, int& pileSize);
	void Shuffle(Card** ppPile, int pileSize);
	Card* DrawCard(Card** ppPile, int& pileSize);

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

