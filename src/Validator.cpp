#include "Validator.h"

Validator::Validator(Deck* _deck, SpecialRules* _rules){
	deck = _deck;
	rules = _rules;
}

void Validator::SetDeck(Deck *_deck){
	deck = _deck;
}
void Validator::SetRules(SpecialRules *_rules){
	rules = _rules;
}
