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
		MenuChoices choice = GetChoice();
		if (choice == MenuChoices::kCloseProgram)
			break;

		ProcessChoice(choice);
		std::cout << "Done." << std::endl;
		system("pause");
	}
	
}

/////////////////////////////////////////////////////////////////
// Prints the sandbox choices.
/////////////////////////////////////////////////////////////////
void DeckSandbox::ShowMenu() const
{
	std::cout << "Cards in hand: " << m_numCardsInHand << std::endl;
	std::cout << "Pick any choice below." << std::endl;
	for (size_t i = 0; i < static_cast<size_t>(MenuChoices::kCount); ++i)
	{
		std::cout << i << ". " << m_menuChoices[i] << std::endl;
	}
}

/////////////////////////////////////////////////////////////////
// Gets the user's input.
/////////////////////////////////////////////////////////////////
DeckSandbox::MenuChoices DeckSandbox::GetChoice() const
{
	size_t userIntInput;

	std::cin >> userIntInput;

	while (!std::cin.good() && userIntInput > static_cast<size_t>(MenuChoices::kCount)) // if input is not good for any reason loop
	{
		std::cin.clear();													// Resets all error flags from cin
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // effectivelly clears the cin stream buffer
		std::cin >> userIntInput;
	}

	return static_cast<MenuChoices>(userIntInput);
}

/////////////////////////////////////////////////////////////////
// Handles the user's choice.
/////////////////////////////////////////////////////////////////
void DeckSandbox::ProcessChoice(MenuChoices choice) 
{
	switch (choice)
	{
	case MenuChoices::kShuffleDrawPile:
		m_deck.ShuffleDrawPile();
		break;
	case MenuChoices::kDrawACard:
		Draw();
		break;
	case MenuChoices::kPrintHand:
		PrintHand();
		break;
	case MenuChoices::kDiscardCard:
		Discard();
		break;
	case MenuChoices::kReshuffleDiscardIntoDraw:
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
void DeckSandbox::PrintHand() const
{
	std::cout << "Printing hand:" << std::endl;
	for (size_t i = 0; i < m_numCardsInHand; ++i)
	{
		std::cout << i << ". " << m_pHand[i]->GetName() << std::endl;
	}
}

/////////////////////////////////////////////////////////////////
// Discards a card of the player's choice.
/////////////////////////////////////////////////////////////////
void DeckSandbox::Discard()
{
	if (m_numCardsInHand <= 0)
	{
		std::cout << "Hand is empty\n";
		return;
	}

	PrintHand();
	std::cout << "Enter the number of the card to discard." << std::endl;
	size_t cardIndex;

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
	
	Card* pDiscard = m_pHand[cardIndex];
	m_deck.AddToDiscardPile(pDiscard);
	--m_numCardsInHand;

	// Shift the rest of the hand down so there are no gaps.
	for (size_t i = cardIndex; i < m_numCardsInHand; ++i)
	{
		m_pHand[i] = m_pHand[i + 1];
	}
}

/////////////////////////////////////////////////////////////////
// Returns the discard pile to the draw pile and shuffles it.
/////////////////////////////////////////////////////////////////
void DeckSandbox::ReturnDiscardToDraw()
{
	Card* pDiscardedCards[52]{ nullptr };
	int numDiscarded = 0;

	// We have to pull from the discard one by one
	while (true)
	{
		Card* pCard = m_deck.DrawFromDiscardPile();
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
