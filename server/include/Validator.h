#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "Deck.h"
#include "SpecialRules.h"

#include "GameModes.h"

class Validator{
	protected:
		Deck* deck;
		SpecialRules* rules;

		GameModes mode;

	public:
		Validator(GameModes _mode = GameModes::Makao, Deck* _deck = nullptr, SpecialRules* _rules = nullptr);
		virtual ~Validator() {};

		virtual bool Validate(Card* card, bool suit = true, bool name = true) = 0;
		virtual std::vector<int> CardValues(std::vector<Card*>, bool suit = true, bool name = true, std::vector<bool> specialParameters = {}) = 0;
		virtual bool ValidateEnd(std::vector<Card*>) = 0;

		void SetDeck(Deck* _deck);
		void SetRules(SpecialRules* _rules);
};

#endif
