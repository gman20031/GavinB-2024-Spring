#pragma once

#include "Deck.h"
#include "Card.h"




/////////////////////////////////////////////////////////////////
// An interactive sandbox for testing the Deck class.
/////////////////////////////////////////////////////////////////
class DeckSandbox
{
private:
	static constexpr size_t kChoiceCount = 6;
	Deck m_deck;
	Card* m_pHand[52];
	size_t m_numCardsInHand;

	enum class MenuChoices
	{
		kShuffleDrawPile = 0,
		kDrawACard,
		kPrintHand,
		kDiscardCard,
		kReshuffleDiscardIntoDraw,
		kCloseProgram,
		kCount,
	};
	
	std::string m_menuChoices[static_cast<size_t>(MenuChoices::kCount)]
	{
		"Shuffle the draw pile",
		"Draw a card",
		"Print your hand",
		"Discard a card",
		"Return discard pile to draw pile and shuffle",
		"Close program"
	};

public:
	DeckSandbox();
	void Run();

private:
	void ShowMenu();
	int GetChoice();
	void ProcessChoice(int choice);

	void Draw();
	void PrintHand();
	void Discard();
	void ReturnDiscardToDraw();
};

