#include <iostream>

#include "Clients/ClientPlayer.h"
#include "Rules/GameMaster.h"
#include "Clients/ClientBot.h"

#include <chrono>

int main(){
	
	srand(time(NULL));

	auto start = std::chrono::high_resolution_clock::now();
	GameMaster master = GameMaster();

	ClientBot player = ClientBot();
	ClientBot bot1 = ClientBot();
	ClientBot bot2 = ClientBot();
	ClientBot bot3 = ClientBot();

	master.AddPlayer(&player);
	master.AddPlayer(&bot1);
	master.AddPlayer(&bot2);
	master.AddPlayer(&bot3);

	master.PrepareGame();
	master.StartGame();
	
	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout<<"runtime duration: "<<duration.count()<<std::endl;

}
