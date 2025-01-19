#ifndef MAKAOVALIDATOR_H
#define MAKAOVALIDATOR_H

#include "Validator.h"

class MakaoValidator : public Validator{

	public:
		MakaoValidator(Deck* _deck = nullptr, SpecialRules* _sr = nullptr);
		
		bool Validate(Card* card) override;
};

#endif
