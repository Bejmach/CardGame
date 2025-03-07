#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <vector>

#include "ClientBot.h"
#include "ClientPlayer.h"
#include "GameMaster.h"

class Server{
	private:
		std::vector<GameMaster* > games;

		bool CreateGame();

		void OnRequest(char* req);

	public:
		Server();

		void Process();
};

#endif
