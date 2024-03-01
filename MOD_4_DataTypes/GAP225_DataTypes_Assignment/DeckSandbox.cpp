#include "DeckSandbox.h"

#include <iostream>

DeckSandbox::DeckSandbox()
	: m_deck{}
	, m_pHand{nullptr}
	, m_numCardsInHand{0}
{
}

/////////////////////////////////////////////////////////////////
// Runs the sandbox simulation.
/////////////////////////////////////////////////////////////////
void DeckSandbox::Run()
{
	while (true)
	{
		system("cls");
		ShowMenu();
		int choice = GetChoice();
		if (choice == kChoiceQuit)
			break;

		ProcessChoice(choice);
		std::cout << "Done." << std::endl;
		system("pause");
	}
	
}

/////////////////////////////////////////////////////////////////
// Prints the sandbox choices.
/////////////////////////////////////////////////////////////////
void DeckSandbox::ShowMenu()
{
	std::cout << "Cards in hand: " << m_numCardsInHand << std::endl;
	std::cout << "Pick any choice below." << std::endl;
	for (int i = 0; i < kChoiceCount; ++i)
	{
		std::cout << i << ". " << m_menuChoices[i] << std::endl;
	}
}

/////////////////////////////////////////////////////////////////
// Gets the user's input.
/////////////////////////////////////////////////////////////////
int DeckSandbox::GetChoice()
{
	int choice;
	std::cin >> choice;
	return choice;
}

/////////////////////////////////////////////////////////////////
// Handles the user's choice.
/////////////////////////////////////////////////////////////////
void DeckSandbox::ProcessChoice(int choice)
{
	switch (choice)
	{
	case kChoiceShuffle:
		m_deck.ShuffleDrawPile();
		break;
	case kChoiceDraw:
		Draw();
		break;
	case kChoicePrintHand:
		PrintHand();
		break;
	case kChoiceDiscard:
		Discard();
		break;
	case kChoiceReturnDiscardToDraw:
		ReturnDiscardToDraw();
		break;
	}
}

/////////////////////////////////////////////////////////////////
// Draws a card from the top of the deck's draw pile.
/////////////////////////////////////////////////////////////////
void DeckSandbox::Draw()
{
	m_pHand[m_numCardsInHand] = m_deck.DrawFromDrawPile();
	++m_numCardsInHand;
}

/////////////////////////////////////////////////////////////////
// Prints your current hand.
/////////////////////////////////////////////////////////////////
void DeckSandbox::PrintHand()
{
	std::cout << "Printing hand:" << std::endl;
	for (int i = 0; i < m_numCardsInHand; ++i)
	{
		std::cout << i << ". " << m_pHand[i]->GetName() << std::endl;
	}
}

/////////////////////////////////////////////////////////////////
// Discards a card of the player's choice.
/////////////////////////////////////////////////////////////////
void DeckSandbox::Discard()
{
	PrintHand();
	std::cout << "Enter the number of the card to discard." << std::endl;
	int cardIndex;

	while (true)
	{
		
		std::cin >> cardIndex;
		if (cardIndex < 0 || cardIndex >= m_numCardsInHand)
		{
			std::cout << "Invalid choice, try again." << std::endl;
		}
		else
		{
			break;
		}
	}
	
	Deck::Card* pDiscard = m_pHand[cardIndex];
	m_deck.AddToDiscardPile(pDiscard);
	--m_numCardsInHand;

	// Shift the rest of the hand down so there are no gaps.
	for (int i = cardIndex; i < m_numCardsInHand; ++i)
	{
		m_pHand[i] = m_pHand[i + 1];
	}
}

/////////////////////////////////////////////////////////////////
// Returns the discard pile to the draw pile and shuffles it.
/////////////////////////////////////////////////////////////////
void DeckSandbox::ReturnDiscardToDraw()
{
	Deck::Card* pDiscardedCards[52]{ nullptr };
	int numDiscarded = 0;

	// We have to pull from the discard one by one
	while (true)
	{
		Deck::Card* pCard = m_deck.DrawFromDiscardPile();
		if (pCard != nullptr)
		{
			pDiscardedCards[numDiscarded] = pCard;
			++numDiscarded;
		}
		else
		{
			// If pCard is null then the discard is empty
			break;
		}
	}

	// Now add to the deck one by one
	for (int i = 0; i < numDiscarded; ++i)
	{
		m_deck.AddToDrawPile(pDiscardedCards[i]);
	}

	// Shuffle when done
	m_deck.ShuffleDrawPile();
}
