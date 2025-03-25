#ifndef CLIENTBASE_H
#define CLIENTBASE_H

#include <SDL2/SDL_net.h>

#include <iostream>

class ClientBase{
	protected:
		const char* SERVER_IP = "127.0.0.1";
		const int PORT = 3350;
		const int BUFFER_SIZE = 128;
	
		bool running = true;

		IPaddress ip;
		TCPsocket socket;

		char* buffer;

		int gameClientId = -1;
		int clientId = -1;

		virtual void ReciveResponce();
		virtual void SendRequest();
	public:
		ClientBase();
		~ClientBase();

		void Prepare();
};

#endif
