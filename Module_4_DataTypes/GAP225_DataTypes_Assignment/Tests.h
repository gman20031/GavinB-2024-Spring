#pragma once

#include "Deck.h"

#include <iostream>

/////////////////////////////////////////////////////////////////
// Simple helper function to print whether the given test has
// passed or not.
/////////////////////////////////////////////////////////////////
void RunTest(const char* pName, bool passes)
{
	std::cout << pName << (passes ? " PASS" : " FAIL") << std::endl;
}

/////////////////////////////////////////////////////////////////
// Checks that all cards in a Deck are different from each other.
/////////////////////////////////////////////////////////////////
bool AllCardsUnique()
{
	Deck deck;
	Card* pCheckPile[52]{ nullptr };
	for (size_t i = 0; i < 52; ++i)
	{
		pCheckPile[i] = deck.DrawFromDrawPile();
		for (size_t j = 0; j < i; ++j)
		{
			if (pCheckPile[i]->GetName() == pCheckPile[j]->GetName())
			{
				return false;
			}
		}
	}
	return true;
}

/////////////////////////////////////////////////////////////////
// Checks that a deck has no more or less than 52 cards.
/////////////////////////////////////////////////////////////////
bool CanDrawExactly52()
{
	Deck deck;
	deck.ShuffleDrawPile();
	Card* pLastDraw = nullptr;
	for (int i = 0; i < 52; ++i)
	{
		pLastDraw = deck.DrawFromDrawPile();
		if (pLastDraw == nullptr)
		{
			std::cout << "Drew a null card too soon." << std::endl;
			return false;
		}
	}
	pLastDraw = deck.DrawFromDrawPile();
	if (pLastDraw != nullptr)
	{
		std::cout << "Drew a non-null 53rd card." << std::endl;
		return false;
	}

	return true;
}

/////////////////////////////////////////////////////////////////
// An extended shuffling effectiveness test. We (arbitrarily)
// consider it OK if shuffling leaves 1.5 or fewer cards unmoved.
/////////////////////////////////////////////////////////////////
bool ShuffleChangesCardOrder()
{
	constexpr int kTestCount = 10'000;
	std::cout << "Testing shuffle effectiveness " << kTestCount << " times." << std::endl;

	Deck deck;

	// Create 2 piles with capacity of 52 so we can compare before and after shuffling.
	Card* pPiles[2][52]{ nullptr };

	// Fill only the first pile.
	// We'll fill the second one in the loop.
	for (int i = 0; i < 52; ++i)
	{
		pPiles[0][i] = deck.DrawFromDrawPile();
	}

	// We're going to swap piles one at a time.
	// This keeps track of which pile we're looking at.
	int currentPileIndex = 0;

	// Keep track of how many times cards don't move after a shuffle
	int sameCardCount = 0;

	// Test many times
	for (int test = 0; test < kTestCount; ++test)
	{
		// Get pointers to each of the two piles.
		// This makes the rest of the logic a bit easier to follow.
		Card** ppPile1 = pPiles[currentPileIndex];
		Card** ppPile2 = pPiles[1 - currentPileIndex];

		// Return check pile in original order
		// (we do it in reverse since we are adding from the bottom upward)
		// Note that we are keeping pointers to the cards in our pile.
		for (int i = 51; i >= 0; --i)
		{
			deck.AddToDrawPile(ppPile1[i]);
		}

		// Shuffle
		deck.ShuffleDrawPile();

		// Now fill the other pile after the shuffle.
		for (int i = 0; i < 52; ++i)
		{
			ppPile2[i] = deck.DrawFromDrawPile();
			if (ppPile1[i]->GetName() == ppPile2[i]->GetName())
			{
				++sameCardCount;
			}
		}
	}

	std::cout << "Cards stayed in place a total of " << sameCardCount << " times." << std::endl;

	// On average, if 1.5 cards don't move during the shuffle
	// we consider that to be reasonable.
	if ((float)sameCardCount > (float)kTestCount * 1.5f)
		return false;
	else
		return true;
}

bool StaticCardStringReturn()
{
	using Face = Card::FaceNames;
	using Suit = Card::SuitNames;

	if (Card::GetName(Face::kAce,	Suit::kHearts)	 !=	"Ace of Hearts"		)	return false;
	if (Card::GetName(Face::kTwo,   Suit::kHearts)	 != "Two of Hearts"		)	return false;
	if (Card::GetName(Face::kThree, Suit::kHearts)	 != "Three of Hearts"	)	return false;
	if (Card::GetName(Face::kFour,  Suit::kHearts)	 != "Four of Hearts"	)	return false;
	if (Card::GetName(Face::kFive,	Suit::kHearts)	 != "Five of Hearts"	)	return false;
	if (Card::GetName(Face::kSix,	Suit::kDiamonds) != "Six of Diamonds"	)	return false;
	if (Card::GetName(Face::kSeven, Suit::kDiamonds) != "Seven of Diamonds"	)	return false;
	if (Card::GetName(Face::kEight, Suit::kDiamonds) != "Eight of Diamonds"	)	return false;
	if (Card::GetName(Face::kNine,	Suit::kClubs)	 != "Nine of Clubs"		)	return false;
	if (Card::GetName(Face::kTen,	Suit::kClubs)	 != "Ten of Clubs"		)	return false;
	if (Card::GetName(Face::kJack,	Suit::kSpades)	 != "Jack of Spades"	)	return false;
	if (Card::GetName(Face::kQueen,	Suit::kSpades)	 != "Queen of Spades"	)	return false;
	if (Card::GetName(Face::kKing,	Suit::kSpades)	 != "King of Spades"	)	return false;

	return true;
}

/////////////////////////////////////////////////////////////////
// Runs all unit tests.
/////////////////////////////////////////////////////////////////
void RunAllTests()
{
	RunTest("All cards unique", AllCardsUnique());
	RunTest("Can draw exactly 52 card", CanDrawExactly52());
	RunTest("Shuffling changes card order", ShuffleChangesCardOrder());
	RunTest("Static get name function", StaticCardStringReturn());


	// draw a hand full of all the cards
	// 
}