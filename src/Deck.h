#ifndef DECK_H
#define DECK_H

#include "CardHolder.h"

class Deck{
	private:
		CardHolder holder = CardHolder();
		Card** deck;
		
	public:
		Deck();
		~Deck();

		void PrepareDeck();
		void ShuffleDeck();
		void PrintDeck();
		void PrintCard(int id);
};

#endif
