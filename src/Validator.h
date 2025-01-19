#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "Deck.h"
#include "SpecialRules.h"

class Validator{
	protected:
		Deck* deck;
		SpecialRules* sr;

	public:
		Validator(Deck* _deck = nullptr, SpecialRules* _sr = nullptr);
		virtual void Validate(Card* card) = 0;
};

#endif
