#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <vector>
#include <stdint.h>

#include "../Clients/ClientBot.h"
#include "../Clients/ClientPlayer.h"
#include "../Rules/GameMaster.h"

class Server{
	private:
		std::vector<GameMaster* > games;

		bool CreateGame();
		bool AddPlayer(uint16_t gameId, ClientBase* client);
		bool PrepGame(uint16_t gameId);
		bool StartGame(uint16_t gameId);

		bool DrawCard(uint16_t gameId, uint8_t localPlayerId);
		bool PlayCard(uint16_t gameId, uint8_t localPlayerId, uint8_t card);

		bool Command(uint64_t command);

	public:
		Server();
};

#endif
