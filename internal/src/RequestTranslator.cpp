#include "../include/RequestTranslator.h"
#include <cstring>

// Server Requests
std::vector<char> RequestTranslator::GetCurrentTurnRequest(char playerId, char suit, char name) {
    std::vector<char> request(3);
    request[0] = 0; // Request type: Current turn
    request[1] = suit; // Forced card suit
    request[2] = name; // Forced card name
    return request;
}

std::vector<char> RequestTranslator::GetGameStateRequest(const std::vector<Card*>& handCards, const std::vector<std::vector<Card*>>& enemyHands) {
    size_t requestSize = 1 + 1 + (handCards.size() * 2) + 1 + enemyHands.size();
    std::vector<char> request(requestSize);
    size_t index = 0;

    request[index++] = 1; // Request type: Game state
    request[index++] = static_cast<char>(handCards.size()); // Number of cards on hand

    // Cards on hand
    for (const auto& card : handCards) {
        uint16_t cardData = (static_cast<uint16_t>(card->GetRawSuit()) << 8) | static_cast<uint16_t>(card->GetRawName());
        request[index++] = static_cast<char>(cardData >> 8); // Suit
        request[index++] = static_cast<char>(cardData & 0xFF); // Name
    }

    // n of cards on enemies hands
    request[index++] = static_cast<char>(enemyHands.size());

    for (const auto& enemyHand : enemyHands) {
        request[index++] = static_cast<char>(enemyHand.size());
    }

    return request;
}

std::vector<char> RequestTranslator::GetTurnResultRequest(bool isValidMove) {
    std::vector<char> request(2);
    request[0] = 2; // Request type: Turn result
    request[1] = isValidMove ? 1 : 0; // Turn result (1 valid, 0 invalid)
    return request;
}

// Client Requests
std::vector<char> RequestTranslator::PlayCardsRequest(char playerLocalId, char gameId, const std::vector<Card*>& cards) {
    size_t requestSize = 1 + 1 + 1 + cards.size();
    std::vector<char> request(requestSize);
    size_t index = 0;

    request[index++] = 0; // Request: Play cards
    request[index++] = playerLocalId;
    request[index++] = gameId;

    // Cards to play
    for (const auto& card : cards) {
        request[index++] = (static_cast<char>(card->GetRawSuit()) << 4) | static_cast<char>(card->GetRawName());
    }

    return request;
}

char RequestTranslator::CreateNewGameRequest() {
    return 1; // Request: Create new game
}

char RequestTranslator::JoinGameRequest(char gameId) {
    return (2 << 8) | gameId; // Request: Join game
}