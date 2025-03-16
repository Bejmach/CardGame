#include "Server.h"

Server::Server(unsigned int port, unsigned int maxClients, unsigned int bufferSize){
	PORT = port;
	MAX_CLIENTS = maxClients;
	BUFFER_SIZE = bufferSize;

	buffer = new char[BUFFER_SIZE];
}
Server::~Server(){
	delete[] buffer;
}

void Server::Prepare(){
	if(SDLNet_Init() < 0){
		std::cerr<<"SDLNet_Init failed: "<<SDLNet_GetError()<<std::endl;
		prepared = false;
		return;
	}
	
	IPaddress ip;
	if(SDLNet_ResolveHost(&ip, NULL, PORT) < 0){
		std::cerr<<"SDlNet_ResolveHost failed: "<<SDLNet_GetError()<<std::endl;
		prepared = false;
		return;
	}

	TCPsocket server = SDLNet_TCP_Open(&ip);
	if(!server){
		std::cerr<<"SDLNet_TCP_Open failed: "<<SDLNet_GetError()<<std::endl;
		prepared = false;
		return;
	}
	prepared = true;
	std::cout<<"server listening on port "<<PORT<<"...\n";

	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(MAX_CLIENTS+1);
	SDLNet_TCP_AddSocket(socketSet, server);

	char buffer[BUFFER_SIZE];
}

