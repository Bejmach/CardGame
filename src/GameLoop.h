#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <iostream>
#include <vector>

#include "PlayerClient.h"
#include "Deck.h"

class GameLoop{
	private:
		std::vector<PlayerClient*> clients;
		Deck* deck;

		int playerTurn = 0;
	
	public:
		GameLoop(Deck* _deck = nullptr);

		void CurTurn();
		void NextTurn();

		Deck* SetDeck();

		void AddPlayer(PlayerClient* client);
};

#endif
