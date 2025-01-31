#include <iostream>

#include "Rules/GameMaster.h"
#include "Clients/ClientBot.h"

int main(){
	
	srand(time(NULL));

	GameMaster master = GameMaster();

	ClientBot bot1 = ClientBot();
	ClientBot bot2 = ClientBot();
	ClientBot bot3 = ClientBot();
	ClientBot bot4 = ClientBot();

	master.AddPlayer(&bot1);
	master.AddPlayer(&bot2);
	master.AddPlayer(&bot3);
	master.AddPlayer(&bot4);

	master.PrepareGame();
	master.StartGame();

}
