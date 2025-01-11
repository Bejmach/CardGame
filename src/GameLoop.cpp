#include "GameLoop.h"


GameLoop::GameLoop(Deck* _deck){
	deck = _deck;
}

void GameLoop::AddPlayer(PlayerClient *client){
	clients.push_back(client);
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
