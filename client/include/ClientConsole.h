#ifndef CLIENTCONSOLE_H
#define CLIENTCONSOLE_H

#include "ClientBase.h"

#include <thread>

class ClientConsole : public ClientBase{
	private:

		void ReciveResponce() override;
		void SendRequest() override;


	public:
		
		void Start();

		std::string ConvertMessage(std::string message);
		void DecodeResponce(char* res);


};

#endif
