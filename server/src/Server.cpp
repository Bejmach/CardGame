#include "../include/Server.h"


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

void Server::HandleRequests(char* req){
	if(req[0] == 0){
		if(games.size()<256){
			games.push_back(new GameMaster());
		}
		else{
			std::cout<<"increase max game size"<<std::endl;
		}
	}
	else if(req[0] == 1){
		//create new clientHandler
		//bind clientHandler to clientUI on Id req[2];
		//add clientHandler to GameMaster on Id = req[1];
	}
	else if(req[0] == 2){
		if(games.size()<req[1]){
			if(!games[req[1]]->GetStarted()){
				games[req[1]]->PrepareGame();
				games[req[1]]->StartGame();
			}
			else{
				std::cout<<"Trying to prepare game that already started"<<std::endl;
			}
		}
		else{
			std::cout<<"Trying to prepare not existins game"<<std::endl;
		}
	}
	else if(req[0] == 3){
		char playerLocalId = req[1];
		char gameId = req[2];
		int cardsSize = req[3];

		if(cardsSize == 0){
			std::cout<<"Tried to play empty hand"<<std::endl;
			return;
		}

		std::vector<Card> cards; 

		for(int i = 0; i<cardsSize; i++){
			Card card = Card(req[4+i*2], req[5+i*2]);
			cards.push_back(card);
		}

		Names usedName = cards[0].GetName();
		for(int i=1; i<cards.size(); i++){
			if(cards[i].GetName()!=usedName){
				std::cout<<"Tried to play cards of different names"<<std::endl;
				return;
			}
		}

		//Get clientHandler of playerLocalId in game
		for(int i=0; i<cards.size(); i++){
			//find cards[i] id in clientHandler
			//play cards[i] id in clientHandler
		}
		//Send ResTurnResult to client
	}
}

