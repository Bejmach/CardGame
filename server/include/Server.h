#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <vector>

#include <SDL2/SDL_net.h>

#include "ClientBot.h"
#include "ClientPlayer.h"
#include "ClientWeb.h"
#include "GameMaster.h"
#include "RequestTranslator.h"
#include "Validator.h"


struct Client{
	TCPsocket socket;
	IPaddress ip;
};

class Server{
	private:
		unsigned int PORT;
		unsigned int MAX_CLIENTS;
		unsigned int BUFFER_SIZE;

		IPaddress ip;
		TCPsocket server;
		SDLNet_SocketSet socketSet;

		char* buffer;

		bool prepared = false;
		std::vector<Client*> clients;
		std::vector<GameMaster* > games;

		bool CreateGame();

		void OnRequest(char* req);
		void SendResponce(unsigned int playerIp, const char* responce);
		void SendResponce(Client* client, const char* responce);

	public:
		Server(unsigned int port = 3350, unsigned int maxClients = 512, unsigned int bufferSize = 128);
		~Server();

		void Prepare();

		void Start();

		void HandleRequests(char* req, Client* client);
};

#endif
