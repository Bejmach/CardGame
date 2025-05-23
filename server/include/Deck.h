#ifndef DECK_H
#define DECK_H

#include "CardHolder.h"

class Deck{
	private:
		int deckSize;

		CardHolder holder = CardHolder();
		std::vector<Card*> deck;
		std::vector<Card*> usedCards;

		void PushBackUsed(bool leaveLast);
	
	public:
		Deck(int _deckSize = 52);
		~Deck();

		void PrepareDeck();
		void ShuffleDeck();
		void PrintDeck();
		void PrintCard(int id);
		void PrintAllUsed();
		void PrintUsed(int id);	

		std::vector<Card*> GetDeck();
		std::vector<Card*> GetUsed();

		Card* GetLastDeck();
		Card* GetLastUsed();

		//ToDo
		//Abstract for TakeCard, and create derived class for macao deck
		Card* TakeCard();
		void UseCard(Card* card);

		int DeckSize();
		int UsedSize();

		void ThrowAway(int howMutch);
		
};

#endif
