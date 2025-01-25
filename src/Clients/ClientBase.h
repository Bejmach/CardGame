#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include "../Cards/Card.h"
#include "../Cards/CardTranslator.h"
#include "../Cards/Deck.h"

#include "../Other/Logger.h"

#include "../Rules/Validator.h"
#include "../Rules/SpecialRules.h"

#include <iostream>
#include <vector>

class ClientBase{
	protected:
		ClientBase* lastPlayer;
		ClientBase* nextPlayer;

		std::vector<Card*> onHand;
		Deck* deck;

		Logger* logger;

		Validator* validator;
		SpecialRules* rules;

		int playerId = 0;

	public:
		virtual void OnTurn() = 0;
		virtual void ChangeCard(std::vector<bool>) = 0;
		
		ClientBase(Deck* _deck = nullptr, Validator* _validator = nullptr, SpecialRules* _rules = nullptr);
		virtual ~ClientBase() {};

		void SetDeck(Deck* _deck);
		void SetValidator(Validator* _validator);
		void SetRules(SpecialRules* rules);
		void SetLogger(Logger* _logger);

		void SetId(int _id);

		void SetLastPlayer(ClientBase* player);
		void SetNextPlayer(ClientBase* player);

		Card* GetCard(int id);
		void DrawCard();
		void PlayCard(int id);

		int HandSize();
};

#endif
