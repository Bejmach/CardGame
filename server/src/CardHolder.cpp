#include "../include/CardHolder.h"

CardHolder::CardHolder(){
	cardList = nullptr;
	Allocate();
}
CardHolder::~CardHolder(){
	Deallocate();
}

void CardHolder::Allocate(){
	if(cardList!=nullptr){
		Deallocate();
	}
	cardList = new Card*[52];
	for(int i=0; i<4; i++){
		for(int j=0; j<13; j++){
			cardList[i*13+j] = new Card(i, j);
		}
	}
}
void CardHolder::Deallocate(){
	if(cardList==nullptr){
		return;
	}
	for(int i=0; i<52; i++){
		delete cardList[i];
	}
	delete[] cardList;
	cardList = nullptr;
}
