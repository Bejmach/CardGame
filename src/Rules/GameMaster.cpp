#include "GameMaster.h"
#include "GameModes.h"

GameMaster::GameMaster(GameModes _mode) : mode(_mode), logger(new Logger()) {
    logger->PushLog("GameMaster initialized.");
}

GameMaster::~GameMaster() {
    delete deck;
    delete validator;
    delete rules;
    delete logger;
}

void GameMaster::PrepareGame() {
    logger->PushLog("Preparing game...");

    delete deck;
    delete validator;
    delete rules;

    deck = nullptr;
    validator = nullptr;
    rules = nullptr;

    if (mode == GameModes::Makao) {
        try {
            deck = new Deck();
            validator = new MakaoValidator();
            rules = new MakaoRules();
        } catch (const std::exception& e) {
            logger->PushLog("Failed to allocate game objects: " + std::string(e.what()));
            throw std::runtime_error("Failed to allocate game objects.");
        }
    } else {
        logger->PushLog("Unsupported game mode.");
        throw std::runtime_error("Unsupported game mode.");
    }

    if (!deck || !validator || !rules) {
        logger->PushLog("Failed to initialize game objects.");
        throw std::runtime_error("Failed to initialize game objects.");
    }

    deck->PrepareDeck();
    deck->ShuffleDeck();

    validator->SetDeck(deck);
    validator->SetRules(rules);
    rules->SetLogger(logger);

    for (int i = 0; i < clients.size(); i++) {
        int lastId = (i - 1 + clients.size()) % clients.size();
        int nextId = (i + 1) % clients.size();
        clients[i]->SetLastPlayer(clients[lastId]);
        clients[i]->SetNextPlayer(clients[nextId]);
        clients[i]->SetDeck(deck);
        clients[i]->SetValidator(validator);
        clients[i]->SetLogger(logger);
        clients[i]->SetId(i);
        clients[i]->SetRules(rules);
    }

    if (mode == GameModes::Makao) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < clients.size(); j++) {
                clients[j]->DrawCard();
            }
        }

        deck->ThrowAway(1);
        while (deck->GetLastUsed()->GetName() != Names::Two &&
               deck->GetLastUsed()->GetName() != Names::Three &&
               deck->GetLastUsed()->GetName() != Names::Four &&
               deck->GetLastUsed()->GetName() != Names::Jack &&
               deck->GetLastUsed()->GetName() != Names::Ace) {
            deck->ThrowAway(1);
        }
    }

    prepared = true;
    logger->PushLog("Game preparation completed.");
}

void GameMaster::AddPlayer(ClientBase* client) {
    clients.push_back(client);
    prepared = false;
    logger->PushLog("Added player with ID: " + std::to_string(client->GetId()));
}

void GameMaster::StartGame() {
    if (!prepared) {
        logger->PushLog("Cannot start game before preparation.");
        throw std::runtime_error("Cannot start game before preparation.");
    }

    clients[0]->OnTurn(false, false, 0, 0);
    logger->PushLog("Game started with player ID: " + std::to_string(clients[0]->GetId()));
}

void GameMaster::SendCurrentTurnRequest(char playerId) {
    Card* lastUsedCard = deck->GetLastUsed();
    if (!lastUsedCard) {
        logger->PushLog("No last used card found.");
        return;
    }

    Suits suit = lastUsedCard->GetSuit();
    Names name = lastUsedCard->GetName();

    std::string suitCode = translate::suit::Codename(suit);
    std::string nameCode = translate::name::Code(name);

    char suitChar = static_cast<char>(translate::raw::Suit(suit));
    char nameChar = static_cast<char>(translate::raw::Name(name));

    std::vector<char> request = RequestTranslator::GetCurrentTurnRequest(playerId, suitChar, nameChar);
    //logger->PushLog("Current turn request for player ID: " + std::to_string(playerId) + " with card: " + nameCode + suitCode);
}

void GameMaster::SendGameStateRequest() {
    for (auto& client : clients) {
        std::vector<Card*> handCards = client->GetHand();
        std::vector<std::vector<Card*>> enemyHands;

        for (auto& enemy : clients) {
            if (enemy != client) {
                enemyHands.push_back(enemy->GetHand());
            }
        }

        std::vector<char> request = RequestTranslator::GetGameStateRequest(handCards, enemyHands);
        //logger->PushLog("Game state request for player ID: " + std::to_string(client->GetId()));
    }
}

void GameMaster::SendPlayCardsRequest(char playerLocalId, const std::vector<Card*>& cards) {
    char gameId = 0; // Example game ID
    std::vector<char> request = RequestTranslator::PlayCardsRequest(playerLocalId, gameId, cards);
    std::string cardList;

    for (const auto& card : cards) {
        cardList += translate::name::Code(card->GetName()) + translate::suit::Codename(card->GetSuit()) + " ";
    }

    //logger->PushLog("Sending play cards request for player ID: " + std::to_string(playerLocalId) + " with cards: " + cardList);
}