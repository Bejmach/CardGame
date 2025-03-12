//
// Created by niewi on 12.03.2025.
//
#include <iostream>
#include <vector>
#include "RequestTranslatorTest.h"

void TestGetCurrentTurnRequest() {
    uint8_t playerId = 3;
    uint8_t request = RequestTranslator::GetCurrentTurnRequest(playerId);
    std::cout << "GetCurrentTurnRequest: " << static_cast<int>(request) << std::endl;
}

void TestGetGameStateRequest() {
    std::vector<Card*> handCards;
    handCards.push_back(new Card(Suits::Heart, Names::Two));
    handCards.push_back(new Card(Suits::Spade, Names::Ace));

    std::vector<std::vector<Card*>> enemyHands = {
        { new Card(Suits::Diamond, Names::Three) },
        { new Card(Suits::Club, Names::King), new Card(Suits::Heart, Names::Queen) }
    };

    std::vector<uint8_t> request = RequestTranslator::GetGameStateRequest(handCards, enemyHands);
    std::cout << "GetGameStateRequest: ";
    for (uint8_t byte : request) {
        std::cout << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

    // Clean up
    for (Card* card : handCards) delete card;
    for (auto& enemyHand : enemyHands) {
        for (Card* card : enemyHand) delete card;
    }
}

void TestGetTurnResultRequest() {
    uint8_t validRequest = RequestTranslator::GetTurnResultRequest(true);
    uint8_t invalidRequest = RequestTranslator::GetTurnResultRequest(false);
    std::cout << "GetTurnResultRequest (valid): " << static_cast<int>(validRequest) << std::endl;
    std::cout << "GetTurnResultRequest (invalid): " << static_cast<int>(invalidRequest) << std::endl;
}

void TestPlayCardsRequest() {
    uint8_t playerLocalId = 1;
    uint8_t gameId = 5;
    std::vector<Card*> cards;
    cards.push_back(new Card(Suits::Heart, Names::Two));
    cards.push_back(new Card(Suits::Spade, Names::Ace));

    std::vector<uint8_t> request = RequestTranslator::PlayCardsRequest(playerLocalId, gameId, cards);
    std::cout << "PlayCardsRequest: ";
    for (uint8_t byte : request) {
        std::cout << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

    for (Card* card : cards) delete card;
}

void TestCreateNewGameRequest() {
    uint8_t request = RequestTranslator::CreateNewGameRequest();
    std::cout << "CreateNewGameRequest: " << static_cast<int>(request) << std::endl;
}

void TestJoinGameRequest() {
    uint8_t gameId = 5;
    uint8_t request = RequestTranslator::JoinGameRequest(gameId);
    std::cout << "JoinGameRequest: " << static_cast<int>(request) << std::endl;
}