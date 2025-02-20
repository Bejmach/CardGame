#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <vector>

#include "../Clients/ClientBot.h"
#include "../Clients/ClientPlayer.h"
#include "../Rules/GameMaster.h"

class Server{
	private:
		std::vector<GameMaster* > games;

		bool CreateGame();
		bool AddPlayer(u_int16_t gameId, ClientBase* client);
		bool PrepGame(u_int16_t gameId);
		bool StartGame(u_int16_t gameId);

		bool DrawCard(u_int16_t gameId, u_int8_t localPlayerId);
		bool PlayCard(u_int16_t gameId, u_int8_t localPlayerId, u_int8_t card);

		bool Command(u_int64_t command);

	public:
		Server();
};

#endif
