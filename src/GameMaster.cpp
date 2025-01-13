#include "GameMaster.h"

GameMaster::GameMaster(GameModes _mode){
	deck = new Deck();
	validator = new Validator();
	loop = new GameLoop();

	deck->PrepareDeck();
	deck->ShuffleDeck();

	validator->SetMode(_mode);
	validator->SetDeck(deck);

	loop->SetDeck(deck);
	loop->SetValidator(validator);

	mode = _mode;
}
GameMaster::~GameMaster(){
	delete deck;
	delete validator;
	delete loop;
}

void GameMaster::AddPlayer(PlayerClient *client){
	loop->AddPlayer(client);
}

void GameMaster::PrepareGame(){
	if(mode == GameModes::makao){
		if(loop->PlayerNumber()<=0){
			std::cout<<"Please wait for more players to join"<<std::endl;
			prepared = false;
			return;
		}
		loop->PrepareGame(mode);
		prepared = true;
	}
}
void GameMaster::StartGame(){
	if(!prepared){
		std::cout<<"Please prepare the game, before starting"<<std::endl;
		return;
	}
	loop->StartGame();
}

GameLoop* GameMaster::GetLoop(){
	return loop;
}
