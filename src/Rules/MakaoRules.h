#ifndef MAKAORULES_H
#define MAKAORULES_H

#include "SpecialRules.h"

#include "../Cards/CardTypes.h"

class MakaoRules : public SpecialRules{
	private:
		Suits forceSuit = Suits::Undefined;
		Names forceName = Names::Undefined;

		int forceTime = 0;
		int numberOfPlayer;

	public:
		MakaoRules(int playerCount = 0);
		~MakaoRules() override {};

		bool Validate(Card* card) override;
		void UpdateOnCard(Card* card) override;
};

#endif
