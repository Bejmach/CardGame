#ifndef MAKAORULES_H
#define MAKAORULES_H

#include "SpecialRules.h"

class MakaoRules : public SpecialRules{
	private:
		Suits forceSuit = Suits::Undefined;
		Names forceName = Names::Undefined;

		int forceTime = 0;
		int numberOfPlayer = 0;

	public:
		bool Validate(Card* card) override;
};

#endif
