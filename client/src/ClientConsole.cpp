#include "../include/ClientConsole.h"
#include "../include/StringOperations.h"
#include "../include/RequestTranslator.h"
#include "../include/CardTranslator.h"
#include <alloca.h>
#include <sys/stat.h>

#include<iostream>
#include<string>

void ClientConsole::ReciveResponce(){
    while (running) {
        int received = SDLNet_TCP_Recv(socket, buffer, BUFFER_SIZE);
        if (received <= 0) {
            std::cout << "Disconnected from server.\n";
            running = false;
            break;
        }
        //std::cout << "\n[Server]: " << buffer << "\n> ";

		DecodeResponce(buffer);
        std::cout.flush(); // Fix input formatting
    }
}


void ClientConsole::SendRequest() {
    while (running) {
		
        std::cout << "> ";
        std::cin.getline(buffer, BUFFER_SIZE);
		std::string request(buffer);	
		std::string newRequest = ConvertMessage(request);
        SDLNet_TCP_Send(socket, newRequest.c_str(), BUFFER_SIZE-1);
    }
}

void ClientConsole::Start(){
	std::thread receiveThread(&ClientConsole::ReciveResponce, this);
    std::thread sendThread(&ClientConsole::SendRequest, this);

    receiveThread.join();
    sendThread.join();

	SDLNet_TCP_Close(socket);
    SDLNet_Quit();
}

std::string ClientConsole::ConvertMessage(std::string message){
	std::vector<std::string> split = SO::Split(message, " ");

	std::cout<<split.size();

	for(int i=0; i<split.size(); i++){
		split[i] = SO::ToLower(split[i]);
	}

	if(split.size() == 2){
		if(split[0] == "new" && split[1] == "game"){
			return RT::ReqNewGame();
		}
	}
	if(split.size() == 3){
		if (split[0] == "start" && split[1] == "game"){
			if(SO::Numeric(split[2])){
				return RT::ReqStartGame(std::stoi(split[2]));
			}
		}
		else if(split[0] == "join" && split[1] == "game"){
			if(SO::Numeric(split[2])){
				return RT::ReqJoinGame(std::stoi(split[2]), clientId);
			}
		}
	}
	if(split.size() >= 3){
		if(split[0] == "play" && split[1] == "card"){
			std::vector<std::string> cardIds = SO::Split(split[2], ";");
			std::string cardsString = "";
			for(int i=0; i<cardIds.size(); i++){
				cardsString += (char)(std::stoi(cardIds[0]));
			}
			return RT::ReqPlayCards(clientId, gameClientId, cardsString);
			
		}
	}
	std::cout<<"Wrong command, list of commands:"<<std::endl<<"new game - create new game"<<std::endl<<"join game {id} - join game"<<std::endl<<"start game {id} - start game"<<std::endl<<"play card {id};{id} - play cards"<<std::endl;
	return message;
}

void ClientConsole::DecodeResponce(char* res){
	if(res[0] == 3){
		clientId = res[1];
	}
	else if(res[0] == 0){
		std::cout<<"Current card on table: "<<translate::name::EN(static_cast<Names>(res[2]))<<" "<<translate::suit::EN(static_cast<Suits>(res[1]))<<std::endl;
	}
	else if(res[0] == 1){
		for(int i=0; i<3; i++){
			if(res[1+i*2]!=-1){
				std::cout<<"Enemie Id "<<res[1+i*2]<<" cards: "<<res[2+i*2]<<std::endl;
			}
		}
		std::cout<<"Your cards"<<std::endl;
		for(int i=0; i<res[7]; i++){
			std::cout<<i<<": "<<translate::name::EN(static_cast<Names>(res[8+i*2]))<<" "<<translate::suit::EN(static_cast<Suits>(res[9+i*2]));
		}
	}
	else if(res[0] == 2){
		if(res[1] == 1){
			std::cout<<"Move valid"<<std::endl;
		}
		else{
			std::cout<<"Move invalid. Do new move"<<std::endl;
		}
	}
}
