#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include <iostream>
#include <vector>

#include "Card.h"
#include "Deck.h"

class PlayerClient{
	
	private:
		std::vector<Card*> onHand;
		Deck* deck;

	public:
		PlayerClient(Deck* _deck = nullptr);

		void SetDeck(Deck* _deck);

		std::vector<Card*> GetCards();
		void DrawCard();
		void PlayCard(int id);

};

#endif
