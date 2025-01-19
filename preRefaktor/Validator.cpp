#include "Validator.h"

Validator::Validator(Deck* _deck, GameModes _mode){
	mode = _mode;
	deck = _deck;
}

void Validator::SetMode(GameModes _mode){
	_mode = mode;
}
void Validator::SetDeck(Deck *_deck){
	deck = _deck;
}

void Validator::ForceName(Names name){
	forceName = name;
}
void Validator::ForceSuit(Suits suit){
	forceSuit = suit;
}

bool Validator::ValidateMakao(Card* card, std::string flags){
	
	if(forceSuit!=Suits::Undefined){
		std::cout<<translate::suit::EN(forceSuit)<<std::endl;
		if(forceSuit == card->GetSuit()){
			return true;
		}
		return false;
	}
	else if(forceName!=Names::Undefined){
		std::cout<<translate::name::EN(forceName)<<std::endl;
		if(forceName == card->GetName()){
			return true;
		}
		return false;
	}
	else{
		Card* lastCard = deck->GetUsed()[deck->UsedSize()-1];
		if(lastCard->GetName() == card->GetName() || lastCard->GetSuit() == card->GetSuit()){
			return true;
		}
		return false;
	}
}

bool Validator::Validate(Card *card, std::string flags){
	if(mode == GameModes::makao){
		bool validateResult = ValidateMakao(card, flags);

		if(validateResult){
			if(card->GetName() == Names::Jack){
				if(flags == "2"){forceName = Names::Two;}
				else if(flags == "3"){forceName = Names::Three;}
				else if(flags == "4"){forceName = Names::Four;}
				else if(flags == "5"){forceName = Names::Five;}
				else if(flags == "6"){forceName = Names::Six;}
				else if(flags == "7"){forceName = Names::Seven;}
				else if(flags == "8"){forceName = Names::Eight;}
				else if(flags == "9"){forceName = Names::Nine;}
				else if(flags == "10"){forceName = Names::Ten;}
				else if(flags == "J"){forceName = Names::Jack;}
				else if(flags == "Q"){forceName = Names::Queen;}
				else if(flags == "K"){forceName = Names::King;}
				else if(flags == "A"){forceName = Names::Ace;}
				else{validateResult = false;}

				if(validateResult){
					std::cout<<"Forced name: "<<flags<<std::endl;
					forceName = Names::Undefined;
					forceTime = numberOfPlayers;
				}
			}
			if(card->GetName() == Names::Ace){
				
				if(flags == "H"){forceSuit = Suits::Heart;}
				else if(flags == "D"){forceSuit = Suits::Diamond;}
				else if(flags == "C"){forceSuit = Suits::Club;}
				else if(flags == "S"){forceSuit = Suits::Spade;}
				else{validateResult = false;}
				
				if(validateResult){
					std::cout<<"Forced suit: "<<flags<<std::endl;
					forceSuit = Suits::Undefined;
					forceTime = numberOfPlayers;
				}
			}

			if(validateResult){
				if(forceTime>0){
					forceTime-=1;
					if(forceTime<=0){
						forceSuit = Suits::Undefined;
						forceName = Names::Undefined;
					}
				}
			}
		}

		return validateResult;
	}
	return false;
}
bool Validator::ValidateResult(PlayerClient* client){
	if(mode == GameModes::makao){
		if(client->HandSize() == 0){
			return true;
		}
		return false;
	}
	return false;
}
void Validator::SetNumberOfPlayers(int players){
	numberOfPlayers = players;
}
