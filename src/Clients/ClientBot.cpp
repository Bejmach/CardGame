#include "ClientBot.h"

ClientBot::ClientBot(Deck* _deck, Validator* _validator){
    this->deck = _deck;
    this->validator = _validator;
}

void ClientBot::OnTurn(){
    std::vector<int> cardValues = validator->CardValues(onHand);

    int id = 0;
    int highest = 0;

    for(int i=0; i<cardValues.size(); i++){
        if(cardValues[i]>highest){
            id = i;
            highest = cardValues[i];
        }
    }

    if(highest == 0){
        DrawCard();
    }
    else{
        PlayCard(id);
    }

    if(validator->ValidateEnd(onHand)){
        std::cout<<"winner"<<std::endl;
        return;
    }

    nextPlayer->OnTurn();
}