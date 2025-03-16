#include "MakaoRules.h"


MakaoRules::MakaoRules(GameModes _mode, int playerCount): SpecialRules(_mode){
	numberOfPlayer = playerCount;
}

std::vector<bool> MakaoRules::Validate(Card *card){
	if(forceSuit!=Suits::Undefined && card->GetSuit() == forceSuit){
		return {true,true};
	}
	else if(forceName!=Names::Undefined && card->GetName() == forceName){
		return {true, true};
	}
	else if(forceSuit!=Suits::Undefined || forceName!=Names::Undefined){
		return {false, false};
	}
	return {true, false};
}
std::vector<bool> MakaoRules::UpdateOnCard(Card *card, int playerId){

	std::vector<bool> returner(2, false);

	if(forcePlayerId == playerId && forceSuit!=Suits::Undefined){
		forceSuit = Suits::Undefined;		
	}

	if(card->GetName() == Names::Ace){
		forcePlayerId = playerId;
		returner[0] = true;
	}
	else if(card->GetName() == Names::Jack){
		returner[1] = true;
	}


	if(card!= nullptr){
		if(forceName != Names::Undefined){
			forceName = Names::Undefined;
		}
	}
	return returner;
}

void MakaoRules::CommandUpdate(std::string command){
	Card card = decode::Str(command);

	if(card.GetName()!=Names::Undefined){
		forceName = card.GetName();
		logger->PushLog("F_N:"+translate::name::Code(card.GetName())+";S:U");
	}
	if(card.GetSuit()!=Suits::Undefined){
		forceSuit = card.GetSuit();
		logger->PushLog("F_N:U;S:"+translate::suit::Codename(card.GetSuit()));
	}
}
std::vector<int> MakaoRules::GetData(){
	return {translate::raw::Name(forceName), translate::raw::Suit(forceSuit)};
}
