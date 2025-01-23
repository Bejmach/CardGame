#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include "../Cards/Card.h"
#include "../Cards/CardTranslator.h"
#include "../Cards/Deck.h"

#include "../Rules/Validator.h"

#include <iostream>
#include <vector>

class ClientBase{
	protected:
		ClientBase* lastPlayer;
		ClientBase* nextPlayer;

		std::vector<Card*> onHand;
		Deck* deck;

		Validator* validator;

	public:
		virtual void OnTurn() = 0;
		
		ClientBase(Deck* _deck = nullptr, Validator* _validator = nullptr);
		virtual ~ClientBase() {};

		void SetDeck(Deck* _deck);
		void SetValidator(Validator* _validator);

		void SetLastPlayer(ClientBase* player);
		void SetNextPlayer(ClientBase* player);

		Card* GetCard(int id);
		void DrawCard();
		void PlayCard(int id);

		int HandSize();
};

#endif
