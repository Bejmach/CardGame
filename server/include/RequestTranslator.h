#ifndef REQUESTTRANSLATOR_H
#define REQUESTTRANSLATOR_H

#include <vector>
#include <cstdint>
#include "Card.h"
#include <cstring>

namespace RT {
		// Server Requests
		std::string ResCurTurn(char playerId, char suit, char name);
		std::string ResGameState(std::vector<Card*> handCards, std::vector<std::pair<char, char>> enemies);
		std::string ResTurnResult(bool isValidMove);

	    // Client Requests
		std::string ReqPlayCards(char playerLocalId, char gameId, std::vector<Card*> cards);
		std::string ReqNewGame();
		std::string ReqJoinGame(char gameId, char clientId);
};

#endif // REQUESTTRANSLATOR_H
