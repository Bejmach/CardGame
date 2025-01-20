#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include "Card.h"
#include "CardTranslator.h"
#include "Deck.h"

#include <iostream>
#include <vector>

class ClientBase{
	protected:
		ClientBase* lastPlayer;
		ClientBase* nextPlayer;

		std::vector<Card*> onHand;
		Deck* deck;

	public:
		virtual void OnTurn() = 0;
		
		ClientBase(Deck* _deck = nullptr);
		
		void SetDeck(Deck* _deck);

		void SetLastPlayer(ClientBase* player);
		void SetNextPlayer(ClientBase* player);

		Card* GetCard(int id);
		void DrawCard();
		void PlayCard(int id);

		int HandSize();
};

#endif
