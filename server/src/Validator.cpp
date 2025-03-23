#include "../include/Validator.h"
#include "../include/GameModes.h"

Validator::Validator(GameModes _mode, Deck* _deck, SpecialRules* _rules){
	deck = _deck;
	rules = _rules;
	mode = _mode;
}

void Validator::SetDeck(Deck *_deck){
	deck = _deck;
}
void Validator::SetRules(SpecialRules *_rules){
	rules = _rules;
}
