#include <iostream>
#include <vector>

#include "../include/CardTranslator.h"
#include "../include/Deck.h"

int randRange(int min, int max){
	return min + rand()%max-min+1;
}


Deck::Deck(int _deckSize){
	deckSize = _deckSize;
}
Deck::~Deck(){
}

void Deck::PushBackUsed(bool leaveLast){
	int deckBaseSize = deck.size();
	if(leaveLast){
		deck.resize(deck.size() + usedCards.size()-1);
	}
	else{
		deck.resize(deck.size() + usedCards.size());
	}
	for(int i=0; i<usedCards.size(); i++){
		if(leaveLast && i==usedCards.size()-1){
			Card* tempCard = usedCards[usedCards.size()-1];

			usedCards.resize(1);
			usedCards[0] = tempCard;
			break;
		}
		deck[deckBaseSize + i] = usedCards[i];
	}
	if(!leaveLast){
		usedCards.resize(0);
	}
}

void Deck::PrepareDeck(){
	deck.resize(deckSize);
	for(int i=0; i<deckSize; i++){
		deck[i] = holder.cardList[i];
	}
}
void Deck::ShuffleDeck(){
	for(int i=0; i<500; i++){
		int card1 = randRange(0, deckSize-1);
		int card2 = randRange(0, deckSize-1);

		Card* tempValue = deck[card2];
		deck[card2] = deck[card1];
		deck[card1] = tempValue;
	}
}

void Deck::PrintCard(int id){
	std::string name = translate::name::Code(deck[id]->GetName());
	std::string suit = translate::suit::Code(deck[id]->GetSuit());

	std::cout<<name<<suit<<std::endl;
}
void Deck::PrintDeck(){
	for(int i=0; i<deck.size(); i++){
		PrintCard(i);
	}
}

void Deck::PrintUsed(int id){
	std::string name = translate::name::Code(usedCards[id]->GetName());
	std::string suit = translate::suit::Code(usedCards[id]->GetSuit());

	std::cout<<name<<suit<<std::endl;
}
void Deck::PrintAllUsed(){
	for(int i=0; i<usedCards.size(); i++){
		PrintUsed(i);
	}
}

Card* Deck::GetLastDeck(){
	return deck[deck.size()-1];
}
Card* Deck::GetLastUsed(){
	if(usedCards.size()<1){
		return nullptr;
	}
	return usedCards[usedCards.size()-1];
}

Card* Deck::TakeCard(){
	Card* pickedCard = deck[deck.size()-1];
	deck.resize(deck.size()-1);

	if(deck.size() == 0 && usedCards.size()>1){
		this->PushBackUsed(true);
	}

	return pickedCard;
}
void Deck::UseCard(Card *card){
	usedCards.push_back(card);
}


void Deck::ThrowAway(int howMutch){
	if(howMutch>deck.size()){
		howMutch = deck.size();
		return;
	}
	for(int i=0; i<howMutch; i++){
		UseCard(TakeCard());
	}
}
int Deck::DeckSize(){
	return deck.size();
}
int Deck::UsedSize(){
	return usedCards.size();
}

std::vector<Card*> Deck::GetDeck(){
	return deck;
}
std::vector<Card*> Deck::GetUsed(){
	return usedCards;
}
