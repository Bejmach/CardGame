#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <vector>

#include "../Clients/ClientBot.h"
#include "../Clients/ClientPlayer.h"
#include "../Rules/GameMaster.h"

class Server{
	private:
		std::vector<GameMaster* > games;

		bool CreateGame();

	public:
		Server();
};

#endif
