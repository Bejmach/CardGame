#include "GameMaster.h"
#include "GameModes.h"

GameMaster::GameMaster(GameModes _mode) {
	mode = _mode;
}

GameMaster::~GameMaster() {
	// if (deck != nullptr) {
	// 	delete deck;
	// 	deck = nullptr;
	// }
	// if (validator != nullptr) {
	// 	delete validator;
	// 	validator = nullptr;
	// }
	// if (rules != nullptr) {
	// 	delete rules;
	// 	rules = nullptr;
	// }
	// if (logger != nullptr) {
	// 	delete logger;
	// 	logger = nullptr;
	// }
}

void GameMaster::PrepareGame() {
    if (deck != nullptr) {
        delete deck;
        deck = nullptr;
    }
    if (validator != nullptr) {
        delete validator;
        validator = nullptr;
    }
    if (rules != nullptr) {
        delete rules;
        rules = nullptr;
    }
    if (logger != nullptr) {
        delete logger;
        logger = nullptr;
    }

    if (mode == GameModes::Makao) {
        deck = new Deck();
        validator = new MakaoValidator();
        rules = new MakaoRules();
    }
    logger = new Logger();

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
}

void GameMaster::AddPlayer(ClientBase* client) {
	clients.push_back(client);
	prepared = false;
}

void GameMaster::StartGame() {
	if (!prepared) {
		std::cout << "Can't start before preparing the game" << std::endl;
		return;
	}

	clients[0]->OnTurn(false, false, 0, 0);
	logger->Save();
}

void GameMaster::SendCurrentTurnRequest(uint8_t playerId) {
	uint8_t request = RequestTranslator::GetCurrentTurnRequest(playerId);
	logger->PushLog("current turn request for player ID: " + std::to_string(playerId));
	//send this request to the server
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

		std::vector<uint8_t> request = RequestTranslator::GetGameStateRequest(handCards, enemyHands);
		logger->PushLog("game state request for player ID: " + std::to_string(client->GetId()));
		//send this request to the server
	}
}

void GameMaster::SendPlayCardsRequest(uint8_t playerLocalId, const std::vector<Card*>& cards) {
	uint8_t gameId = 0; // get game ID
	std::vector<uint8_t> request = RequestTranslator::PlayCardsRequest(playerLocalId, gameId, cards);
	std::string cardList;

	for (const auto& card : cards) {
		cardList += translate::name::Code(card->GetName()) + translate::suit::Codename(card->GetSuit()) + " ";

	}
	logger->PushLog("Sending play cards request for player ID: " + std::to_string(playerLocalId) + " with cards: " + cardList);
	//send this request to the server
}