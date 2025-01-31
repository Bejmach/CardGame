#include <iostream>

#include "Clients/ClientPlayer.h"
#include "Rules/GameMaster.h"
#include "Clients/ClientBot.h"

int main(){
	
	srand(time(NULL));

	GameMaster master = GameMaster();

	ClientPlayer player = ClientPlayer();
	ClientBot bot1 = ClientBot();
	ClientBot bot2 = ClientBot();
	ClientBot bot3 = ClientBot();

	master.AddPlayer(&player);
	master.AddPlayer(&bot1);
	master.AddPlayer(&bot2);
	master.AddPlayer(&bot3);

	master.PrepareGame();
	master.StartGame();

}
