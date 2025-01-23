#include "ClientBase.h"

ClientBase::ClientBase(Deck* _deck, Validator* _validator){
	deck = _deck;
	validator = _validator;
}

void ClientBase::SetDeck(Deck *_deck){
	deck = _deck;
}
void ClientBase::SetValidator(Validator* _validator){
	validator = _validator;
}

void ClientBase::SetLastPlayer(ClientBase *player){
	lastPlayer = player;
}
void ClientBase::SetNextPlayer(ClientBase *player){
	nextPlayer = player;
}

Card* ClientBase::GetCard(int id){
	if(id<0 || id>=onHand.size()){
		return nullptr;
	}
	return onHand[id];
}

void ClientBase::DrawCard(){
	onHand.push_back(deck->TakeCard());
}
void ClientBase::PlayCard(int id){
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

int ClientBase::HandSize(){
	return onHand.size();
}
