#ifndef PLAYERPERSON_H
#define PLAYERPERSON_H

#include "iostream"

#include "PlayerClient.h"
#include "CardTranslator.h"
#include "StringOperations.h"
#include "GameLoop.h"

class PlayerPerson : public PlayerClient{
	
	private:
		GameLoop* loop;

	public:
		void OnTurn() override;

		PlayerPerson(GameLoop* _loop = nullptr);

		void SetLoop(GameLoop* _loop);

		void PrintCard(int id);
		void PrintHand();

		void SendCommand(std::string command);
		void AwaitCommand();
};

#endif
