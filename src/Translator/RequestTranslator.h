#ifndef REQUESTTRANSLATOR_H
#define REQUESTTRANSLATOR_H

#include <cstdint>
#include <vector>
#include "../Cards/Card.h"
#include "../Cards/CardTypes.h"

class RequestTranslator {
public:
    // Server Requests
    static uint8_t GetCurrentTurnRequest(uint8_t playerId);
    static std::vector<uint8_t> GetGameStateRequest(const std::vector<Card*>& handCards, const std::vector<std::vector<Card*>>& enemyHands);
    static uint8_t GetTurnResultRequest(bool isValidMove);

    // Client Requests
    static std::vector<uint8_t> PlayCardsRequest(uint8_t playerLocalId, uint8_t gameId, const std::vector<Card*>& cards);
    static uint8_t CreateNewGameRequest();
    static uint8_t JoinGameRequest(uint8_t gameId);
};

#endif // REQUESTTRANSLATOR_H