#include "PlayerClient.h"

PlayerClient::PlayerClient(Deck* _deck){
	deck = _deck;
}

void PlayerClient::SetDeck(Deck *_deck){
	deck = _deck;
}

void PlayerClient::SetLastPlayer(PlayerClient *player){
	lastPlayer = player;
}
void PlayerClient::SetNextPlayer(PlayerClient *player){
	nextPlayer = player;
}

Card* PlayerClient::GetCard(int id){
	if(id<0 || id>=onHand.size()){
		return nullptr;
	}
	return onHand[id];
}

void PlayerClient::DrawCard(){
	onHand.push_back(deck->TakeCard());
}
void PlayerClient::PlayCard(int id){
	Card* card = GetCard(id);
	if(card==nullptr){
		return;
	}
	deck->UseCard(card);
	onHand[id] = nullptr;

	for(int i=id; i<onHand.size()-1; i++){
		onHand[i] = onHand[i+1];
	}
	onHand.resize(onHand.size()-1);
}

int PlayerClient::HandSize(){
	return onHand.size();
}
