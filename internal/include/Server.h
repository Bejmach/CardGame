#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <vector>

#include <SDL2/SDL_net.h>

#include "ClientBot.h"
#include "ClientPlayer.h"
#include "GameMaster.h"

struct Client{
	TCPsocket socket;
	IPaddress ip;
};

class Server{
	private:
		unsigned int PORT;
		unsigned int MAX_CLIENTS;
		unsigned int BUFFER_SIZE;

		SDLNet_SocketSet socketSet;

		char* buffer;

		bool prepared = false;
		std::vector<Client> clients;
		std::vector<GameMaster* > games;

		bool CreateGame();

		void OnRequest(char* req);
		void SendRequest(unsigned int playerIp);

	public:
		Server(unsigned int port = 3350, unsigned int maxClients = 512, unsigned int bufferSize = 128);
		~Server();	
	
		void Prepare();

		void Process();
};

#endif
