#include "../include/ClientConsole.h"

#include <iostream>

int main(){
	
	ClientConsole* client = new ClientConsole();
	
	client->Prepare();

	client->Start();

	delete client;
}
