#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include <iostream>
#include <vector>

#include "Card.h"
#include "Deck.h"

class PlayerClient{
	protected:
		std::vector<Card*> onHand;
		Deck* deck;

	public:
		virtual void OnTurn() = 0;

		PlayerClient(Deck* _deck = nullptr);

		void SetDeck(Deck* _deck);

		void DrawCard();
		void PlayCard(int id);

};

#endif
