#ifndef SPECIALRULES_H
#define SPECIALRULES_H

#include "Card.h"

class SpecialRules{
	private:
		
	public:
		virtual bool Validate(Card* card) = 0;
		virtual void UpdatedOnCard(Card* card) = 0;

};

#endif
