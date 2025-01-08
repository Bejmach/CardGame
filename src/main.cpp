#include <iostream>

#include "Deck.h"

int main(){
	Deck deck = Deck();
	deck.PrepareDeck();
	deck.PrintDeck();

	std::cout<<std::endl<<std::endl<<"Shyffled:"<<std::endl;

	deck.ShuffleDeck();
	deck.PrintDeck();

	return 0;
}
