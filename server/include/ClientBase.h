#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include "Card.h"
#include "CardTranslator.h"
#include "Deck.h"

#include "Logger.h"

#include "Validator.h"
#include "SpecialRules.h"

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
		virtual void OnTurn(bool _stopTurn, bool _drawCard, int _stopTurns, int _drawNumber) = 0;
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
		bool DrawCard();
		void PlayCard(int id);

		int HandSize();

		int GetHighestId(bool suit, bool name, int* draws, int* highest = nullptr);

		int GetId() const { return playerId; }

		std::vector<Card*> GetHand();
};

#endif
