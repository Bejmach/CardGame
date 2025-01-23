#include <iostream>

#include "Rules/GameMaster.h"
#include "Clients/ClientBot.h"

int main(){
	
	srand(time(NULL));

	GameMaster master = GameMaster();

	std::cout<<"1; "<<std::endl;

	ClientBot bot1 = ClientBot();
	ClientBot bot2 = ClientBot();

	std::cout<<"2; "<<std::endl;

	master.AddPlayer(&bot1);
	master.AddPlayer(&bot2);
	
	std::cout<<"3; "<<std::endl;

	master.PrepareGame();

	std::cout<<"4; "<<std::endl;

	master.StartGame();
	
	std::cout<<"5; "<<std::endl;

}
