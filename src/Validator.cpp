#include "Validator.h"

Validator::Validator(GameModes _mode){
	mode = _mode;
}

void Validator::SetMode(GameModes _mode){
	_mode = mode;
}

void Validator::ForceName(Names name){
	forceName = name;
}
void Validator::ForceSuit(Suits suit){
	forceSuit = suit;
}

bool Validator::ValidateMakao(Card* card){
	if(forceSuit==Suits::Undefined){
		if(forceSuit == card->GetSuit()){
			return true;
		}
		return false;
	}
	else if(forceName==Names::Undefined){
		if(forceName == card->GetName()){
			return true;
		}
		return false;
	}
	else{
		Card* lastCard = deck->ShowUsed()[deck->UsedSize()-1];
		if(lastCard->GetName() == card->GetName() || lastCard->GetSuit() == card->GetSuit()){
			return true;
		}
		return false;
	}
}

bool Validator::Validate(Card *card){
	if(mode == GameModes::makao){
		return ValidateMakao(card);
	}
	return false;
}

