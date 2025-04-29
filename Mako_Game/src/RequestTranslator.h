#ifndef REQUESTTRANSLATOR_H
#define REQUESTTRANSLATOR_H

#include <iostream>

#include <vector>
#include <cstdint>
#include "Card.h"
#include <cstring>

namespace RT{
		// Server Requests
		std::string ResCurTurn(char suit, char name);
		std::string ResGameState(std::vector<Card*> handCards, std::vector<std::pair<char, char>> enemies);
		std::string ResTurnResult(bool isValidMove);
		std::string ResPlayerData(char clientId, char clientGameId);

	    // Client Requests
		std::string ReqNewGame();
		std::string ReqStartGame(char gameId);
		std::string ReqJoinGame(char gameId, char clientId);
		std::string ReqPlayCards(char gameId, char playerLocalId, std::string cardsIds);
};

#endif // REQUESTTRANSLATOR_H
