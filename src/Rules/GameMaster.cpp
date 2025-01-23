#include "GameMaster.h"
#include "GameModes.h"

GameMaster::GameMaster(GameModes _mode){
	mode = _mode;
}

GameMaster::~GameMaster(){
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
}

void GameMaster::PrepareGame(){
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
	if(mode == GameModes::Makao){
		deck = new Deck();
		validator = new MakaoValidator();
		rules = new MakaoRules();
	}

	deck->PrepareDeck();
	deck->ShuffleDeck();

	validator->SetDeck(deck);
	validator->SetRules(rules);

	for(int i=0; i<clients.size(); i++){
		int lastId = i-1;
		if(lastId<=-1){
			lastId = clients.size()-1;
		}
		int nextId = i+1;
		if(nextId>=clients.size()){
			nextId = 0;
		}
		clients[i]->SetLastPlayer(clients[lastId]);
		clients[i]->SetNextPlayer(clients[nextId]);

		clients[i]->SetDeck(deck);
		clients[i]->SetValidator(validator);
	}

	prepared = true;
}

void GameMaster::AddPlayer(ClientBase* client){
	clients.push_back(client);
	prepared = false;
}

void GameMaster::StartGame(){
	if(!prepared){
		std::cout<<"Can't start before preparing the game"<<std::endl;
		return;
	}
	clients[0]->OnTurn();
}