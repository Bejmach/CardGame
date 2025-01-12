#include "GameLoop.h"


GameLoop::GameLoop(Deck* _deck, Validator* _validator){
	deck = _deck;
	validator = _validator;
}

void GameLoop::AddPlayer(PlayerClient *client){
	clients.push_back(client);
}

void GameLoop::PrepareGame(GameModes mode){
	if(mode == GameModes::makao){
		for(int i=0; i<5; i++){
			for(int j=0; j<clients.size(); j++){
				clients[j]->DrawCard();
			}
		}
		deck->ThrowAway(1);
		while(deck->UsedSize()<=0 && (deck->GetUsed()[deck->UsedSize()-1]->GetName()!=Names::Ace && deck->GetUsed()[deck->UsedSize()-1]->GetName()!=Names::Two && deck->GetUsed()[deck->UsedSize()-1]->GetName()!=Names::Three && deck->GetUsed()[deck->UsedSize()-1]->GetName()!=Names::Four && deck->GetUsed()[deck->UsedSize()-1]->GetName()!=Names::Jack && deck->GetUsed()[deck->UsedSize()-1]->GetName()!=Names::King)){
			deck->ThrowAway(1);
		}
	}
}

void GameLoop::CurTurn(){
	std::cout<<"Player turn "<<playerTurn<<std::endl;
	clients[playerTurn]->OnTurn();
}
void GameLoop::NextTurn(){
	playerTurn+=1;
	if(playerTurn>=clients.size()){
		playerTurn = 0;
	}
	if(playerTurn<0){
		playerTurn = clients.size()-1;
	}
	std::cout<<std::endl<<std::endl;
	CurTurn();
}
bool GameLoop::ValidateMove(Card* card){
	return validator->Validate(card);
}

void GameLoop::SetDeck(Deck *_deck){
	deck = _deck;
}
void GameLoop::SetValidator(Validator *_validator){
	validator = _validator;
}

void GameLoop::PrintCurGameState(){
	std::cout<<"In deck: "<<std::endl;
	deck->PrintDeck();
	std::cout<<std::endl<<std::endl<<"Already used: "<<std::endl;
	deck->PrintAllUsed();
	std::cout<<std::endl<<std::endl<<"On hands: "<<std::endl;
	for(int i=0; i<clients.size(); i++){
		std::cout<<"Player "<<i<<":"<<std::endl;
		clients[i]->PrintHand();
		std::cout<<std::endl;
	}
}
