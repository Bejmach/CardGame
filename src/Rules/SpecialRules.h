#ifndef SPECIALRULES_H
#define SPECIALRULES_H

#include "../Cards/Card.h"

#include "GameModes.h"

class SpecialRules{
	private:
		GameModes mode;
		
	public:
		SpecialRules(GameModes _mode = GameModes::Makao);
		virtual ~SpecialRules() {};

		virtual bool Validate(Card* card) = 0;
		virtual void UpdateOnCard(Card* card) = 0;

};

#endif
