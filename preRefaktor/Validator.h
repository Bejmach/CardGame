#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "Deck.h"
#include "PlayerClient.h"

enum class GameModes{makao};

class Validator{
	private:
		GameModes mode;
		Deck* deck;
		Suits forceSuit = Suits::Undefined;
		Names forceName = Names::Undefined;

		int numberOfPlayers = 0;
		int forceTime = 0;

		bool ValidateMakao(Card* card, std::string flags);

	public:
		Validator(Deck* deck = nullptr, GameModes _mode = GameModes::makao);

		void SetMode(GameModes _mode);
		void SetDeck(Deck* _deck);

		void ForceSuit(Suits suit);
		void ForceName(Names name);

		bool Validate(Card* card, std::string flags);
		bool ValidateResult(PlayerClient* client);

		void SetNumberOfPlayers(int players);
};

#endif
