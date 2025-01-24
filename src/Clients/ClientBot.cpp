#include "ClientBot.h"

ClientBot::ClientBot(Deck* _deck, Validator* _validator){
    this->deck = _deck;
    this->validator = _validator;
}

bool ClientBot::Step(bool first){

    bool suit = true;
    bool name = true;

    if(!first){
        suit = false;
    }

    std::vector<int> cardValues = validator->CardValues(onHand, suit, name);

    int id = 0;
    int highest = 0;

    for(int i=0; i<cardValues.size(); i++){
        if(cardValues[i]>highest){
            id = i;
            highest = cardValues[i];
        }
    }

    if(highest != 0){
        PlayCard(id);
        return true;
    }
    else if(first){
        DrawCard();
        return false;
    }
    return false;
}

void ClientBot::OnTurn(){
    Step(true);
    bool canStep = true;

    while(canStep){
        canStep = Step(false);
    }

    

    if(validator->ValidateEnd(onHand)){
        std::cout<<"winner"<<std::endl;
        return;
    }

    nextPlayer->OnTurn();
}