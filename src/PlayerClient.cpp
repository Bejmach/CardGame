#include "PlayerClient.h"

PlayerClient::PlayerClient(Deck* _deck){
	deck = _deck;
}
void PlayerClient::SetDeck(Deck *_deck){
	deck = _deck;
}

void PlayerClient::DrawCard(){
	onHand.push_back(deck->TakeCard());
}
void PlayerClient::PlayCard(int id){
	if(id>=onHand.size() || id<0){
		return;
	}
	deck->UseCard(onHand[id]);
	onHand[id] = nullptr;
	for(int i=id; i<onHand.size()-1; i++){
		onHand[i] = onHand[i+1];
	}
	onHand.resize(onHand.size()-1);


}
