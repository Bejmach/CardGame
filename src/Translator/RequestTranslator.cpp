#include "RequestTranslator.h"

// Server Requests
uint8_t RequestTranslator::GetCurrentTurnRequest(uint8_t playerId) {
    return (0 << 6) | (playerId & 0x3F); // 1 byte: request type (0) + playerId
}

std::vector<uint8_t> RequestTranslator::GetGameStateRequest(const std::vector<Card*>& handCards, const std::vector<std::vector<Card*>>& enemyHands) {
    std::vector<uint8_t> request;
    request.push_back(1); //Request type: Game state

    //Number of cards on hand
    request.push_back(static_cast<uint8_t>(handCards.size()));

    //Cards on hand
    for (const auto& card : handCards) {
        uint16_t cardData = (static_cast<uint16_t>(card->GetRawSuit()) << 8) | static_cast<uint16_t>(card->GetRawName());
        request.push_back(static_cast<uint8_t>(cardData >> 8)); // Suit
        request.push_back(static_cast<uint8_t>(cardData & 0xFF)); // Name
    }

    //Number of cards on enemies hands
    uint8_t numberOfEnemies = enemyHands.size();
    request.push_back(numberOfEnemies);

    for (const auto& enemyHand : enemyHands) {
        request.push_back(static_cast<uint8_t>(enemyHand.size()));
    }

    return request;
}

uint8_t RequestTranslator::GetTurnResultRequest(bool isValidMove) {
    return isValidMove ? 1 : 0; // 1 byte: turn result (1 for valid, 0 for invalid)
}

//Client Requests
std::vector<uint8_t> RequestTranslator::PlayCardsRequest(uint8_t playerLocalId, uint8_t gameId, const std::vector<Card*>& cards) {
    std::vector<uint8_t> request;
    request.push_back(0); //Request: Play cards
    request.push_back(playerLocalId);
    request.push_back(gameId);

    // Cards to play
    for (const auto& card : cards) {
        uint8_t cardData = (static_cast<uint8_t>(card->GetRawSuit()) << 4) | static_cast<uint8_t>(card->GetRawName());
        request.push_back(cardData);
    }

    return request;
}

uint8_t RequestTranslator::CreateNewGameRequest() {
    return 1; //Request:Create new game
}

uint8_t RequestTranslator::JoinGameRequest(uint8_t gameId) {
    return (2 << 8) | gameId; //Request: Join game
}