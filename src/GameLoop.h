#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <iostream>
#include <vector>

#include "PlayerClient.h"
#include "Deck.h"
#include "Validator.h"


class GameLoop{
	private:
		std::vector<PlayerClient*> clients;
		Deck* deck;
		Validator* validator;

		int playerTurn = 0;
	
	public:
		GameLoop(Deck* _deck = nullptr, Validator* _validator = nullptr);

		void CurTurn();
		void NextTurn();

		//GameModes in Validator
		void PrepareGame(GameModes mode);

		bool ValidateMove(Card* card);

		void SetDeck(Deck* _deck);
		void SetValidator(Validator* _validator);

		void AddPlayer(PlayerClient* client);

		void PrintCurGameState();
};

#endif
