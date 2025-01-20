#include "GameMaster.h"

GameMaster::GameMaster(){
	deck = new Deck();
	validator = new MakaoValidator();
	rules = new MakaoRules();

	validator->SetDeck(deck);
	validator->SetRules(rules);
}

GameMaster::~GameMaster(){
	delete deck;
	delete validator;
	delete rules;
}
