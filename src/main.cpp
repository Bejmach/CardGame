#include <iostream>

#include "Deck.h"

int main(){
	Deck deck = Deck();
	deck.PrepareDeck();
	deck.PrintDeck();

	std::cout<<std::endl<<std::endl<<"Shyffled:"<<std::endl;

	deck.ShuffleDeck();
	deck.DEBUGThrowAway(52);

	deck.PrintDeck();
	std::cout<<deck.DEBUGDeckSize()<<std::endl;

	std::cout<<std::endl<<std::endl<<"Used:"<<std::endl;
	deck.PrintAllUsed();

	return 0;
}
