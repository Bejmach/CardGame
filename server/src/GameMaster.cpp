#include "../include/GameMaster.h"
#include <string>

GameMaster::GameMaster(GameModes _mode) : mode(_mode), logger(new Logger()) {
    logger->PushLog("GameMaster initialized.");
}

GameMaster::~GameMaster() {
	if(deck != nullptr){
		delete deck;
		deck = nullptr;
	}
	if(validator != nullptr){
		delete validator;
		validator = nullptr;
	}
	if(rules != nullptr){
		delete rules;
		rules = nullptr;
	}
	if(logger != nullptr){
		delete logger;
		logger = nullptr;
	}
}

void GameMaster::PrepareGame() {

    if(deck != nullptr){
		delete deck;
		deck = nullptr;
	}
	if(validator != nullptr){
		delete validator;
		validator = nullptr;
	}
	if(logger != nullptr){
		delete logger;
		logger = nullptr;
	}
	if(rules != nullptr){
		delete rules;
		rules = nullptr;
	}
	if(mode == GameModes::Makao){
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
        while (deck->GetLastUsed()->GetName() == Names::Two ||
               deck->GetLastUsed()->GetName() == Names::Three ||
               deck->GetLastUsed()->GetName() == Names::Four ||
               deck->GetLastUsed()->GetName() == Names::Jack ||
               deck->GetLastUsed()->GetName() == Names::Ace  ||
			   deck->GetLastUsed()->GetName() == Names::King) {
            deck->ThrowAway(1);
        }
    }

    prepared = true;
}

void GameMaster::AddPlayer(ClientBase* client) {
	if(clients.size()<4){
		clients.push_back(client);
		prepared = false;
		logger->PushLog("P_J: " + std::to_string(clients.size()-1));
	}
}

void GameMaster::StartGame() {
    if (!prepared) {
		std::cout<<"Cant start before preparing the game"<<std::endl;
	}

	started = true;

    clients[0]->OnTurn(false, false, 0, 0);

	logger->Save();
}

bool GameMaster::GetStarted(){
	return started;
}
Validator* GameMaster::GetValidator(){
	return validator;
}
std::vector<ClientBase*> GameMaster::GetClients(){
	return clients;
}
