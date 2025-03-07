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
	if(logger != nullptr){
		delete logger;
		logger = nullptr;
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
	if(logger != nullptr){
		delete logger;
		logger = nullptr;
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

		clients[i]->SetLogger(logger);
		clients[i]->SetId(i);

		clients[i]->SetRules(rules);
	}

	if(mode == GameModes::Makao){
		for(int i=0; i<5; i++){
			for(int j=0; j<clients.size(); j++){
				clients[j]->DrawCard();
			}
		}
		deck->ThrowAway(1);
		while(deck->GetLastUsed()->GetName()!=Names::Two && deck->GetLastUsed()->GetName()!=Names::Three && deck->GetLastUsed()->GetName()!=Names::Four && deck->GetLastUsed()->GetName()!=Names::Jack && deck->GetLastUsed()->GetName()!=Names::Ace){
			deck->ThrowAway(1);
		}
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

	

	clients[0]->OnTurn(false, false, 0, 0);

	logger->Save();
}