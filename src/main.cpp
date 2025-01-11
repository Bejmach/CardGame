#include <iostream>

#include "Deck.h"
#include "PlayerClient.h"
#include "PlayerPerson.h"
#include "GameLoop.h"

int main(){
	
	PlayerPerson player = PlayerPerson();
	PlayerPerson player2 = PlayerPerson();

	Deck deck = Deck();
	GameLoop loop = GameLoop(&deck);

	deck.PrepareDeck();
	deck.ShuffleDeck();

	loop.AddPlayer(&player);
	loop.AddPlayer(&player2);

	player.SetLoop(&loop);
	player.SetDeck(&deck);
	player2.SetLoop(&loop);
	player2.SetDeck(&deck);
	
	std::cout<<"Game started"<<std::endl;
	loop.CurTurn();
	

	return 0;
}
