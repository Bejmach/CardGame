#include "MakaoValidator.h"

MakaoValidator::MakaoValidator(GameModes _mode, Deck* _deck, SpecialRules* _rules) : Validator(_mode, _deck, _rules){}

bool MakaoValidator::Validate(Card* card){
	if(!rules->Validate(card)){
		return false;
	}
	if(card->GetSuit() == deck->GetLastUsed()->GetSuit() || card->GetName() == deck->GetLastUsed()->GetName()){
		return true;
	}
	return false;
}
bool MakaoValidator::ValidateEnd(std::vector<Card*> cards){
	if(cards.size() == 0){
		return true;
	}
	return false;
}

std::vector<int> MakaoValidator::CardValues(std::vector<Card*> cards){
	std::vector<int> cardValues(cards.size());

	std::vector<int> cardSuits(4, 0);

	for(int i=0; i<cards.size(); i++){
		if(cards[i]->GetSuit() == Suits::Heart){
			cardSuits[0] += 1;
		}
		else if(cards[i]->GetSuit() == Suits::Diamond){
			cardSuits[1] += 1;
		}
		else if(cards[i]->GetSuit() == Suits::Club){
			cardSuits[2] += 1;
		}
		else if(cards[i]->GetSuit() == Suits::Spade){
			cardSuits[3] += 1;
		}
	}

	for(int i=0; i<cards.size(); i++){
		if(!Validate(cards[i])){
			cardValues[i] = -1;
		}
		else if(cardSuits[cards[i]->GetRawSuit()] == 1){
			cardValues[i] = 3;
		}
		else if(cards[i]->GetName() == Names::Ace || cards[i]->GetName() == Names::Jack || cards[i]->GetName() == Names::Two || cards[i]->GetName() == Names::Three || cards[i]->GetName() == Names::Four){
			cardValues[i] = 2;
		}
		else{
			cardValues[i] = 1;
		}
	}

	return cardValues;
}
