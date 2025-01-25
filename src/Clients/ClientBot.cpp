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

void ClientBot::ChangeCard(std::vector<bool> actions){
    if(actions[0]){
        std::vector<int> suits(4, 0);
        for(int i=0; i<onHand.size(); i++){
            suits[translate::raw::Suit(onHand[i]->GetSuit())] +=1;
        }

        int id = 0;
        int highest = 0;

        for(int i=0; i<suits.size(); i++){
            if(suits[i]>highest){
                highest = suits[i];
                id = i;
            }
        }

        rules->CommandUpdate(translate::suit::Id(id));
    }
    else if(actions[1]){
        std::vector<int> names(13, 0);
        for(int i=0; i<onHand.size(); i++){
            if(i!=0 && i!=1 && i!=2 && i!= 9 && i!=10 && i!=11 && i!=12){
                names[translate::raw::Name(onHand[i]->GetName())] +=1;
            }
        }

        int id = 3;
        int highest = 0;

        for(int i=0; i<names.size(); i++){
            if(names[i]>highest){
                highest = names[i];
                id = i;
            }
        }

        rules->CommandUpdate(translate::name::Id(id));
    }
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