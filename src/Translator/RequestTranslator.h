#ifndef REQUESTTRANSLATOR_H
#define REQUESTTRANSLATOR_H

#include <vector>
#include <cstdint>
#include "Card.h"
#include <cstring>

class RequestTranslator {
public:
    // Server Requests
    static std::vector<char> GetCurrentTurnRequest(char playerId, char suit, char name);
    static std::vector<char> GetGameStateRequest(const std::vector<Card*>& handCards, const std::vector<std::vector<Card*>>& enemyHands);
    static std::vector<char> GetTurnResultRequest(bool isValidMove);

    // Client Requests
    static std::vector<char> PlayCardsRequest(char playerLocalId, char gameId, const std::vector<Card*>& cards);
    static char CreateNewGameRequest();
    static char JoinGameRequest(char gameId);
};

#endif // REQUESTTRANSLATOR_H