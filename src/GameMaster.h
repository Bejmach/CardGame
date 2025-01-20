#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "ClientBase.h"
#include "Validator.h"
#include "SpecialRules.h"
#include "Deck.h"

#include "MakaoValidator.h"
#include "MakaoRules.h"

#include <iostream>
#include <vector>

class GameMaster{
	private:
		std::vector<ClientBase*> clients;
		Validator* validator;
		SpecialRules* rules;
		Deck* deck;

	public:
		GameMaster();
		~GameMaster();
};

#endif
