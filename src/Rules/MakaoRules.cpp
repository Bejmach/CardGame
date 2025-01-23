#include "MakaoRules.h"


MakaoRules::MakaoRules(int playerCount){
	numberOfPlayer = playerCount;
}

bool MakaoRules::Validate(Card *card){
	if(forceSuit!=Suits::Undefined && card->GetSuit() == forceSuit){
		return true;
	}
	else if(forceName!=Names::Undefined && card->GetName() == forceName){
		return true;
	}
	else if(forceSuit!=Suits::Undefined || forceName!=Names::Undefined){
		return false;
	}
	return true;
}
void MakaoRules::UpdateOnCard(Card *card){
	forceTime = 0;
	if(forceTime == 0){
		forceName = Names::Undefined;
		forceSuit = Suits::Undefined;
	}
}
