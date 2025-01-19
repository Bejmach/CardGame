#include <iostream>

#include "Deck.h"
#include "PlayerClient.h"
#include "PlayerPerson.h"
#include "GameLoop.h"
#include "GameMaster.h"

int main(){
	
	srand(time(NULL));

	/*PlayerPerson player = PlayerPerson();
	PlayerPerson player2 = PlayerPerson();

	Deck deck = Deck();
	GameLoop loop = GameLoop(&deck);
	Validator validator = Validator();

	validator.SetDeck(&deck);
	validator.SetMode(GameModes::makao);

	deck.PrepareDeck();
	deck.ShuffleDeck();
	
	loop.SetValidator(&validator);
	loop.AddPlayer(&player);
	loop.AddPlayer(&player2);

	player.SetLoop(&loop);
	player.SetDeck(&deck);
	player2.SetLoop(&loop);
	player2.SetDeck(&deck);

	loop.PrepareGame(GameModes::makao);

	loop.PrintCurGameState();
	
	std::cout<<std::endl<<"Game started"<<std::endl;
	loop.CurTurn();*/

	GameMaster master = GameMaster(GameModes::makao);
	
	PlayerPerson player = PlayerPerson();
	PlayerPerson player2 = PlayerPerson();

	player.SetLoop(master.GetLoop());
	player2.SetLoop(master.GetLoop());

	master.AddPlayer(&player);
	master.AddPlayer(&player2);

	master.StartGame();

	master.PrepareGame();

	master.StartGame();

	return 0;
}
