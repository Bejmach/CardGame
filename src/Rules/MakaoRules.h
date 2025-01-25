#ifndef MAKAORULES_H
#define MAKAORULES_H

#include "SpecialRules.h"

#include "../Cards/CardTypes.h"

#include "../Cards/CardTranslator.h"

class MakaoRules : public SpecialRules{
	private:
		Suits forceSuit = Suits::Undefined;
		Names forceName = Names::Undefined;

		int forceTime = 0;
		int numberOfPlayer;

		int forcePlayerId = 0;

	public:
		MakaoRules(GameModes _mode = GameModes::Makao, int playerCount = 0);
		~MakaoRules() override {};

		std::vector<bool> Validate(Card* card) override;
		std::vector<bool> UpdateOnCard(Card *card, int playerId) override;

		void CommandUpdate(std::string command) override;
};

#endif
