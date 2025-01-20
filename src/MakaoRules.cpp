#include "MakaoRules.h"

MakaoRules::MakaoRules(int playerCount){
	numberOfPlayer = playerCount;
}

bool MakaoRules::Validate(Card *card){
	return false;
}
void MakaoRules::UpdateOnCard(Card *card){
	forceTime = 0;
}
