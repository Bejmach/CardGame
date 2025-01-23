#ifndef MAKAOVALIDATOR_H
#define MAKAOVALIDATOR_H

#include "GameModes.h"
#include "Validator.h"

#include "../Cards/CardTranslator.h"

class MakaoValidator : public Validator{

	public:
		MakaoValidator(GameModes _mode = GameModes::Makao, Deck* _deck = nullptr, SpecialRules* _sr = nullptr);
		~MakaoValidator() override{};

		bool Validate(Card* card) override;
		bool ValidateEnd(std::vector<Card*>) override;

		std::vector<int> CardValues(std::vector<Card*>) override;
};

#endif
