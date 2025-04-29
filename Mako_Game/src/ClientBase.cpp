#include "ClientBase.h"

ClientBase::ClientBase(Deck* _deck, Validator* _validator, SpecialRules* _rules){
	deck = _deck;
	validator = _validator;
	rules = _rules;
}

void ClientBase::SetDeck(Deck *_deck){
	deck = _deck;
}
void ClientBase::SetValidator(Validator* _validator){
	validator = _validator;
}
void ClientBase::SetRules(SpecialRules* _rules){
	rules = _rules;
}
void ClientBase::SetLogger(Logger* _logger){
	logger = _logger;
}

void ClientBase::SetId(int _id) {
    if (_id < 0) {
        throw std::invalid_argument("Player id negative");
    }
    playerId = _id;
}
int ClientBase::GetId(){
	return playerId;
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

bool ClientBase::DrawCard(){
	Card* card = deck->TakeCard();
	onHand.push_back(card);

	std::string cardCode = translate::name::Code(card->GetName())+translate::suit::Codename(card->GetSuit());
	std::string lastCode;
	if(deck->DeckSize()+deck->UsedSize()-1 <= 0){
		logger->PushLog("T_NC");
		std::cout<<"Terminating, not enought cards to play"<<std::endl;
		return false;
	}
	if(deck->GetLastUsed() == nullptr){
		lastCode = "NULL";
	}
	else{
		lastCode = translate::name::Code(deck->GetLastUsed()->GetName())+translate::suit::Codename(deck->GetLastUsed()->GetSuit());
	}

	logger->PushLog(std::to_string(playerId)+";D_"+ cardCode + " -- " + lastCode);
	return true;
}
void ClientBase::PlayCard(int id){

	Card* card = GetCard(id);
	if(card==nullptr){
		return;
	}
	std::string cardCode = translate::name::Code(card->GetName())+translate::suit::Codename(card->GetSuit());
	std::string lastCode;
	if(deck->GetLastUsed() == nullptr){
		lastCode = "NULL";
	}
	else{
		lastCode = translate::name::Code(deck->GetLastUsed()->GetName())+translate::suit::Codename(deck->GetLastUsed()->GetSuit());
	}

	logger->PushLog(std::to_string(playerId)+";P_"+ cardCode + " -> " + lastCode);

	deck->UseCard(card);

	std::vector<bool> actions = rules->UpdateOnCard(card, playerId);

	ChangeCard(actions);

	onHand[id] = nullptr;

	for(int i=id; i<onHand.size()-1; i++){
		onHand[i] = onHand[i+1];
	}
	onHand.resize(onHand.size()-1);
}

int ClientBase::HandSize(){
	return onHand.size();
}

int ClientBase::GetHighestId(bool suit, bool name, int* draws, int *highest){
	std::vector<int> cardValues = validator->CardValues(onHand, suit, name, {*draws!=0});

	bool deleteHighest = false;
    int id = 0;
	
	if(highest==nullptr){
    	*highest = 0;
		deleteHighest = true;
	}

    for(int i=0; i<cardValues.size(); i++){
        if(cardValues[i]>*highest){
            id = i;
            *highest = cardValues[i];
        }
    }
	if(deleteHighest){
		delete highest;
	}
	return id;
}

std::vector<Card*> ClientBase::GetHand() {
	return onHand;
}
