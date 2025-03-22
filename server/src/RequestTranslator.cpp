#include "../include/RequestTranslator.h"
#include <cstring>

unsigned int BUFFER_SIZE = 128;


// Server Requests
std::string RT::ResCurTurn(char playerId, char suit, char name) {
	
	std::string responce;
	responce.resize(BUFFER_SIZE);

	responce[0] = 0;
	responce[1] = suit;
	responce[2] = name;
	
	return responce;
}

std::string RT::ResGameState(std::vector<Card*> handCards, std::vector<std::pair<char, char>> enemies) {
	
	std::string responce;
	responce.resize(BUFFER_SIZE);

	responce[0] = 1;

	for(int i=0; i<3; i++){
		if(i<enemies.size()){
			responce[1+i*2] = enemies[i].first;
			responce[2+i*2] = enemies[i].second;
		}
	}

    // Cards on hand
    for(int i=0; i<handCards.size(); i++) {
        responce[7+i*2] = static_cast<char>(handCards[i]->GetName()); // Suit
        responce[8+i*2] = static_cast<char>(handCards[i]->GetSuit()); // Name
    }

    return responce;
}

std::string RT::ResTurnResult(bool isValidMove) {
    std::string responce;
	responce.resize(BUFFER_SIZE);
    responce[0] = 2; // Request type: Turn result
    responce[1] = isValidMove ? 1 : 0; // Turn result (1 valid, 0 invalid)
    return responce;
}

// Client Requests
std::string RT::ReqPlayCards(char playerLocalId, char gameId, std::vector<Card*> cards) {
	std::string request;
	request.resize(BUFFER_SIZE);

    request[0] = 0; // Request: Play cards
    request[1] = playerLocalId;
    request[2] = gameId;
	request[3] = cards.size();

    // Cards to play
    for(int i=0; i<cards.size(); i++) {
        request[4+i] = static_cast<char>(cards[i]->GetSuit());
		request[5+i] = static_cast<char>(cards[i]->GetName());
    }

    return request;
}

std::string RT::ReqNewGame() {
	std::string request;
	request.resize(BUFFER_SIZE);
	
	request[0] = 1;

	return request;
}

std::string RT::ReqJoinGame(char gameId, char clientId) {
	std::string request;
	request.resize(BUFFER_SIZE);

	request[0] = 2;
	request[1] = gameId;
	request[2] = clientId;

	return request;
}
