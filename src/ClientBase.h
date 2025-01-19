#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include "Card.h"
#include "CardTranslator.h"
#include "Deck.h"

#include <iostream>
#include <vector>

class PlayerClient{
	protected:
		PlayerClient* lastPlayer;
		PlayerClient* nextPlayer;

		std::vector<Card*> onHand;
		Deck* deck;

	public:
		virtual void OnTurn() = 0;
		
		PlayerClient(Deck* _deck = nullptr);
		
		void SetDeck(Deck* _deck);

		void SetLastPlayer(PlayerClient* player);
		void SetNextPlayer(PlayerClient* player);

		Card* GetCard(int id);
		void DrawCard();
		void PlayCard(int id);

		int HandSize();
};

#endif
