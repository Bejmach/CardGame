#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "Deck.h"

enum class GameModes{makao};

class Validator{
	private:
		GameModes mode;
		Deck* deck;
		Suits forceSuit;
		Names forceName;

		bool ValidateMakao(Card* card);

	public:
		Validator(Deck* deck = nullptr, GameModes _mode = GameModes::makao);

		void SetMode(GameModes _mode);
		void SetDeck(Deck* _deck);

		void ForceSuit(Suits suit);
		void ForceName(Names name);

		bool Validate(Card* card);
};

#endif
