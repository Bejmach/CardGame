#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <vector>

#include <SDL2/SDL_net.h>

#include "ClientBot.h"
#include "ClientPlayer.h"
#include "GameMaster.h"

const unsigned int PORT = 3350;
const unsigned int MAX_CLIENTS = 512;
const unsigned int BUFFER_SIZE = 128;

struct Client{
	TCPsocket socket;
	IPaddress ip;
};

class Server{
	

	private:
		std::vector<Client> clients;
		std::vector<GameMaster* > games;

		bool CreateGame();

		void OnRequest(char* req);
		void SendRequest(unsigned int playerIp);

	public:
		Server();
		void Prepare();

		void Process();
};

#endif
