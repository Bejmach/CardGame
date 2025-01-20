#include "MakaoValidator.h"

MakaoValidator::MakaoValidator(Deck* _deck, SpecialRules* _rules) : Validator(_deck, _rules){}

bool MakaoValidator::Validate(Card* card){
	if(!rules->Validate(card)){
		return false;
	}
	if(card->GetSuit() == deck->GetLastUsed()->GetSuit() || card->GetName() == deck->GetLastUsed()->GetName()){
		return true;
	}
	return false;
}
