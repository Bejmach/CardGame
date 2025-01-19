#include "MakaoValidator.h"

MakaoValidator::MakaoValidator(Deck* _deck, SpecialRules* _sr) : Validator(_deck, _sr){}

bool MakaoValidator::Validate(Card* card){
	if(!sr->Validate(card)){
		return false;
	}
	if(card->GetSuit() == deck->GetLastUsed()->GetSuit() || card->GetName() == deck->GetLastUsed()->GetName()){
		return true;
	}
	return false;
}
