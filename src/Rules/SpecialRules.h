#ifndef SPECIALRULES_H
#define SPECIALRULES_H

#include "../Cards/Card.h"
#include "../Other/Logger.h"

#include "GameModes.h"


class SpecialRules{
	protected:
		GameModes mode;

		Logger* logger;
		
	public:
		SpecialRules(GameModes _mode = GameModes::Makao);
		virtual ~SpecialRules();

		//{can use, force use}
		virtual std::vector<bool> Validate(Card* card) = 0;
		virtual std::vector<bool> UpdateOnCard(Card *card, int playerId) = 0;
		virtual std::vector<int> GetData() = 0;

		virtual void CommandUpdate(std::string command) = 0;

		void SetLogger(Logger* _logger);
};

#endif
