#include "../include/ClientBase.h"
#include <SDL2/SDL_net.h>

ClientBase::ClientBase(){
	buffer =  new char[128];
}
ClientBase::~ClientBase(){
	delete[] buffer;
}

void ClientBase::ReciveResponce(){
    while (running) {
        int received = SDLNet_TCP_Recv(socket, buffer, BUFFER_SIZE);
        if (received <= 0) {
            std::cout << "Disconnected from server.\n";
            running = false;
            break;
        }
        std::cout << "\n[Server]: " << buffer << "\n> ";
        std::cout.flush(); // Fix input formatting
    }
}


void ClientBase::SendRequest() {
    while (running) {
        std::cout << "> ";
        std::cin.getline(buffer, BUFFER_SIZE);
        SDLNet_TCP_Send(socket, buffer, strlen(buffer) + 1);
    }
}

void ClientBase::Prepare(){
	if (SDLNet_Init() < 0) {
        std::cerr << "SDLNet_Init failed: " << SDLNet_GetError() << std::endl;
        return;
    }

    if (SDLNet_ResolveHost(&ip, SERVER_IP, PORT) < 0) {
        std::cerr << "SDLNet_ResolveHost failed: " << SDLNet_GetError() << std::endl;
        return;
    }

    socket = SDLNet_TCP_Open(&ip);
    if (!socket) {
        std::cerr << "SDLNet_TCP_Open failed: " << SDLNet_GetError() << std::endl;
        return;
    }

    std::cout << "Connected to server! Type messages to send.\n";
}
