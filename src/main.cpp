#include <iostream>

#include "Deck.h"
#include "PlayerClient.h"
#include "PlayerPerson.h"


int main(){
	Deck deck = Deck();
	deck.PrepareDeck();
	
	PlayerClient client = PlayerClient(&deck);
	PlayerPerson person = PlayerPerson(&client);

	std::cout<<"Game ready"<<std::endl;
	while(true){
		person.AwaitCommand();
		std::cout<<std::endl<<std::endl<<"deck: "<<std::endl;
		deck.PrintDeck();
		std::cout<<std::endl<<std::endl<<"hand: "<<std::endl;
		person.PrintHand();
		std::cout<<std::endl<<std::endl<<"used: "<<std::endl;
		deck.PrintAllUsed();
	}
	

	return 0;
}
