#include <iostream>

#include "../include/ClientPlayer.h"
#include "../include/GameMaster.h"
#include "../include/ClientBot.h"

#include "../include/Server.h"

#include <chrono>

int main(){
	/*
	srand(time(NULL));

	auto start = std::chrono::high_resolution_clock::now();
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
	
	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout<<"runtime duration: "<<duration.count()<<std::endl;
	*/
	Server* server = new Server();
	server->Prepare();

	while(true){
		server->Process();
	}

	delete server;
}
