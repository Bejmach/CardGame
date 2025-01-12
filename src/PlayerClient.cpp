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

Card* PlayerClient::GetCard(int id){
	std::cout<<id<<std::endl;
	if(id<0 || id>=onHand.size()){
		return nullptr;
	}
	return onHand[id];
}

void PlayerClient::PrintCard(int id){
	if(id>=onHand.size() || id<0){
		return;
	}
	Card* card = onHand[id];
	std::string suit = translate::suit::EN(card->GetSuit());
	std::string name = translate::name::EN(card->GetName());

	std::cout<<name<<" of "<<suit<<std::endl;
}
void PlayerClient::PrintHand(){
	for(int i=0; i<onHand.size(); i++){
		PrintCard(i);
	}
}
