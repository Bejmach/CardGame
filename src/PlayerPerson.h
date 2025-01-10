#ifndef PLAYERPERSON_H
#define PLAYERPERSON_H

#include "iostream"

#include "PlayerClient.h"
#include "CardTranslator.h"
#include "StringOperations.h"

class PlayerPerson{
	
	private:
		PlayerClient* client;

	public:
		PlayerPerson(PlayerClient* _client = nullptr);
		void SetClient(PlayerClient* _client);

		void PrintCard(int id);
		void PrintHand();

		void PlayCard(int id);
		void DrawCard();

		void SendCommand(std::string command);
		void AwaitCommand();
};

#endif
