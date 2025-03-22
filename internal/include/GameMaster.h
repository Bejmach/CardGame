#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "ClientBase.h"
#include "Validator.h"
#include "SpecialRules.h"
#include "Deck.h"
#include "CardTranslator.h"
#include "Logger.h"
#include "MakaoValidator.h"
#include "MakaoRules.h"
#include "GameModes.h"
#include "RequestTranslator.h"

#include <iostream>
#include <vector>

class GameMaster {
private:
	std::vector<ClientBase*> clients;
	Validator* validator = nullptr;
	SpecialRules* rules = nullptr;
	Deck* deck = nullptr;
	Logger* logger = nullptr;
	GameModes mode;
	bool prepared = false;

public:
	GameMaster(GameModes _mode = GameModes::Makao);
	~GameMaster();

	void PrepareGame();
	void AddPlayer(ClientBase* client);
	void StartGame();
	void SetLogger(Logger* _logger);
	void SendCurrentTurnRequest(char playerId);
	void SendGameStateRequest();
	void SendPlayCardsRequest(char playerLocalId, const std::vector<Card*>& cards);
};

#endif