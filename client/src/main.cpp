#include "../include/ClientBase.h"

int main(){
	ClientBase* client = new ClientBase();

	client->Prepare();

	client->Start();

	delete client;
}
