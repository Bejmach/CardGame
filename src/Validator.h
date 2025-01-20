#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "Deck.h"
#include "SpecialRules.h"

class Validator{
	protected:
		Deck* deck;
		SpecialRules* rules;

	public:
		Validator(Deck* _deck = nullptr, SpecialRules* _rules = nullptr);
		virtual bool Validate(Card* card) = 0;

		void SetDeck(Deck* _deck);
		void SetRules(SpecialRules* _rules);
};

#endif
