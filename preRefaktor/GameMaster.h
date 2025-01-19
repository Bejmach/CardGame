#ifndef GAMEMASTER_CPP
#define GAMEMASTER_CPP

#include "GameLoop.h"
#include "Validator.h"
#include "PlayerClient.h"

class GameMaster{
	private:
		Deck* deck;
		Validator* validator;
		GameLoop* loop;

		GameModes mode;

		bool prepared = false;

	public:
		GameMaster(GameModes _mode = GameModes::makao);
		~GameMaster();

		void AddPlayer(PlayerClient* client);
		void PrepareGame();
		void StartGame();

		GameLoop* GetLoop();
};

#endif
