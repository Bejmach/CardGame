#include "Card.h"

Card::Card(Suits _suit, Names _name){
	suit = _suit;
	name = _name;
}
Card::Card(int _suit, int _name){
	if(_suit<4 && _suit>=0 && _name<13 && _name>=0){
		suit = static_cast<Suits>(_suit);
		name = static_cast<Names>(_name);
	}
	else{
		suit = Suits::Heart;
		name = Names::Two;
	}
}

Names Card::GetName() const {
    return name;
}

Suits Card::GetSuit() const {
    return suit;
}

int Card::GetRawName() const {
    return static_cast<int>(name);
}

int Card::GetRawSuit() const {
    return static_cast<int>(suit);
}
