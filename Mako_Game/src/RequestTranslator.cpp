#include "RequestTranslator.h"
#include <cstring>

unsigned int BUFFER_SIZE = 128;


// Server Requests
std::string RT::ResCurTurn(char suit, char name) {
	
	std::string responce;
	responce.resize(BUFFER_SIZE);

	responce[0] = 0;
	responce[1] = suit;
	responce[2] = name;
	
	return responce;
}

//enemieId::number of cards
std::string RT::ResGameState(std::vector<Card*> handCards, std::vector<std::pair<char, char>> enemies) {
	
	std::string responce;
	responce.resize(BUFFER_SIZE);

	responce[0] = 1;

	for(int i=0; i<3; i++){
		if(i<enemies.size()){
			responce[1+i*2] = enemies[i].first;
			responce[2+i*2] = enemies[i].second;
		}
		else{
			responce[1+i*2] = -1;
			responce[2+i*2] = -1;
		}
	}
	responce[7] = handCards.size();
    // Cards on hand
    for(int i=0; i<handCards.size(); i++) {
        responce[8+i*2] = static_cast<char>(handCards[i]->GetName()); // Suit
        responce[9+i*2] = static_cast<char>(handCards[i]->GetSuit()); // Name
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

std::string RT::ResPlayerData(char clientId, char clientGameId){
	std::string responce;
	responce.resize(BUFFER_SIZE);
	responce[0] = 3;
	responce[1] = clientId;
	responce[2] = clientGameId;
	return responce;
}

// Client Requests

std::string RT::ReqNewGame() {
	std::string request;
	request.resize(BUFFER_SIZE);
	
	request[0] = 0;

	return request;
}

std::string RT::ReqJoinGame(char gameId, char clientId) {
	std::string request;
	request.resize(BUFFER_SIZE);

	request[0] = 1;
	request[1] = gameId;
	request[2] = clientId;

	return request;
}
std::string RT::ReqStartGame(char gameId){
	std::string request;
	request.resize(BUFFER_SIZE);

	request[0] = 2;
	request[1] = gameId;
	
	return request;
}
std::string RT::ReqPlayCards(char gameId, char playerLocalId, std::string cardsIds) {
	std::string request;
	request.resize(BUFFER_SIZE);

    request[0] = 3; // Request: Play cards
    request[1] = playerLocalId;
    request[2] = gameId;
	request[3] = cardsIds.size();

    // Cards to play
    for(int i=0; i<cardsIds.size(); i++) {
		request[4+i] = cardsIds[i];
    }

    return request;
}


