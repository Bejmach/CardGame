#include "../include/Server.h"
#include "SDL_net.h"
#include <SDL2/SDL_net.h>


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

	if(SDLNet_ResolveHost(&ip, NULL, PORT) < 0){
		std::cerr<<"SDlNet_ResolveHost failed: "<<SDLNet_GetError()<<std::endl;
		prepared = false;
		return;
	}

	server = SDLNet_TCP_Open(&ip);
	if(!server){
		std::cerr<<"SDLNet_TCP_Open failed: "<<SDLNet_GetError()<<std::endl;
		prepared = false;
		return;
	}
	prepared = true;
	std::cout<<"server listening on port "<<PORT<<"...\n";

	socketSet = SDLNet_AllocSocketSet(MAX_CLIENTS+1);
	SDLNet_TCP_AddSocket(socketSet, server);
}

void Server::Start(){
	while(true){
		if(socketSet == NULL || server == NULL){
			return;
		}
		SDLNet_CheckSockets(socketSet, 1000);
		TCPsocket clientSocket = SDLNet_TCP_Accept(server);
		if(clientSocket){
			Client* newClient = new Client({clientSocket, *SDLNet_TCP_GetPeerAddress(clientSocket)});
			clients.push_back(newClient);
			SDLNet_TCP_AddSocket(socketSet, clientSocket);
			std::cout<<"New client connected"<<std::endl;
		}
		for(size_t i=0; i<clients.size(); i++){
			if(SDLNet_SocketReady(clients[i]->socket)){
				int received = SDLNet_TCP_Recv(clients[i]->socket, buffer, BUFFER_SIZE);
				if(received<=0){
					std::cout<<"client disconected"<<std::endl;
					SDLNet_TCP_DelSocket(socketSet, clients[i]->socket);
					SDLNet_TCP_Close(clients[i]->socket);
					clients.erase(clients.begin()+i);
					i--;
				}
				else{
					std::cout<<"Message received: "<<buffer<<std::endl;
				}
			}
		}
	}
}

void Server::HandleRequests(char* req, Client* client){
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

		if(gameId>=games.size()){
			std::cout<<"Tried to play in not existing game"<<std::endl;
			return;
		}

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

		GameMaster* master = games[gameId];

		ClientBase* clientBase = master->GetClients()[playerLocalId];
		//find cards in player hand and play them
		for(int i=0; i<cards.size(); i++){
			std::vector<Card*> clientCards = clientBase->GetHand(); 
			for(int j=0; j<clientCards.size(); j++){
				if(clientCards[j]->GetName() == cards[i].GetName() && clientCards[j]->GetSuit() == cards[i].GetSuit()){
					clientBase->PlayCard(j);
				}
			}
		}
		for(int i=0; i<clients.size(); i++){
			if(clients[i] == client){
				SendResponce(i, RT::ResTurnResult(true).c_str());
			}
		}
	}
}
void Server::SendResponce(unsigned int playerId, const char* responce){
	if(playerId>=clients.size()){
		return;
	}
	SDLNet_TCP_Send(clients[playerId]->socket, responce, strlen(responce)+1);
}

