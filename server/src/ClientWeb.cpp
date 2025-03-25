#include "../include/ClientWeb.h"

ClientWeb::ClientWeb(Deck* _deck, Validator* _validator){
	deck = _deck;
	validator = _validator;
}

void ClientWeb::ChangeCard(std::vector<bool> actions){
}
void ClientWeb::OnTurn(bool _stopTurn, bool _drawCard, int _stopTurns, int _drawNumber){}


