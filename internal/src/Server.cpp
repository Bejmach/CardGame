#include "Server.h"

Server::Server(){
	if(SDLNet_Init() < 0){
		std::cerr<<"SDLNet_Init failed: "<<SDLNet_GetError()<<std::endl;
		return 1;
	}
	
	IPaddress ip;
	if(SDLNet_ResolveHost(&ip, NULL, PORT) < 0){
		std::cerr<<"SDlNet_ResolveHost failed: "<<SDLNet_GetError()<<std::endl;
		return 1;
	}

	TCPsocket server = SDLNet_TCP_Open(&ip);
	if(!server){
		std::cerr<<"SDLNet_TCP_Open failed: "<<SDLNet_GetError()<<std::endl;
		return 1;
	}

	std::cout<<"server listening on port "<<PORT<<"...\n";

	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(MAX_CLIENTS+1);
	SDLNet_TCP_AddSocket(socketSet, server);

	char buffer[BUFFER_SIZE];
}

Server::Prepare(){
	if(SDLNet_Init() < 0){
		std::cerr<<"SDLNet_Init failed: "<<SDLNet_GetError()<<std::endl;
		return 1;
	}
	
	IPaddress ip;
	if(SDLNet_ResolveHost(&ip, NULL, PORT) < 0){
		std::cerr<<"SDlNet_ResolveHost failed: "<<SDLNet_GetError()<<std::endl;
		return 1;
	}

	TCPsocket server = SDLNet_TCP_Open(&ip);
	if(!server){
		std::cerr<<"SDLNet_TCP_Open failed: "<<SDLNet_GetError()<<std::endl;
		return 1;
	}

	std::cout<<"server listening on port "<<PORT<<"...\n";

	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(MAX_CLIENTS+1);
	SDLNet_TCP_AddSocket(socketSet, server);

	char buffer[BUFFER_SIZE];
}

