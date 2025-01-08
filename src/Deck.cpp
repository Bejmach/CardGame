#include <iostream>
#include <vector>

#include "CardTranslator.h"
#include "Deck.h"

int randRange(int min, int max){
	return min + rand()%max-min+1;
}


Deck::Deck(){
	deck = new Card*[52];
}
Deck::~Deck(){
	delete[] deck;
}

void Deck::PrepareDeck(){
	for(int i=0; i<52; i++){
		deck[i] = holder.cardList[i];
	}
}
void Deck::ShuffleDeck(){
	for(int i=0; i<500; i++){
		int card1 = randRange(0, 51);
		int card2 = randRange(0, 51);

		Card* tempValue = deck[card2];
		deck[card2] = deck[card1];
		deck[card1] = tempValue;
	}
}

void Deck::PrintCard(int id){
	std::string name = translate::name::EN(deck[id]->GetName());
	std::string suit = translate::suit::EN(deck[id]->GetSuit());

	std::cout<<name<<" of "<<suit<<std::endl;
}
void Deck::PrintDeck(){
	for(int i=0; i<52; i++){
		PrintCard(i);
	}
}
