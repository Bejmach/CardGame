#include <iostream>

#include "Rules/GameMaster.h"
#include "Clients/ClientBot.h"

int main(){
	
	srand(time(NULL));

	GameMaster master = GameMaster();

	ClientBot bot1 = ClientBot();
	ClientBot bot2 = ClientBot();

	master.AddPlayer(&bot1);
	master.AddPlayer(&bot2);

	master.PrepareGame();
	master.StartGame();

}
