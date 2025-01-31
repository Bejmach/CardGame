#include "ClientBot.h"

ClientBot::ClientBot(Deck* _deck, Validator* _validator){
    this->deck = _deck;
    this->validator = _validator;
}

bool ClientBot::Step(bool first, bool _stopTurn, bool _drawCard, int *stops, int *draws, bool* backshoot){

    bool suit = true;
    bool name = true;

    if(!first){
        suit = false;
    }

    if(_stopTurn){
        suit = false;
    }

    std::vector<int> cardValues = validator->CardValues(onHand, suit, name, {*draws!=0});

    int id = 0;
    int highest = 0;

    for(int i=0; i<cardValues.size(); i++){
        if(cardValues[i]>highest){
            id = i;
            highest = cardValues[i];
        }
    }

    if(highest != 0){

        if(onHand[id]->GetName() == Names::Two){
            *draws += 2;
        }
        else if(onHand[id]->GetName() == Names::Three){
            *draws += 3;
        }
        else if(onHand[id]->GetName() == Names::King){
            if(onHand[id]->GetSuit() == Suits::Heart){
                *draws += 5;
            }
            else if(onHand[id]->GetSuit() == Suits::Spade){
                *draws += 5;
                *backshoot = true;
            }
        }
        else if(onHand[id]->GetName() == Names::Four){
            *stops+=1;
        }

        PlayCard(id);
        return true;
    }
    else if(first){
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

void ClientBot::OnTurn(bool _stopTurn, bool _drawCard, int _stopTurns, int _drawNumber){
    bool canStep = true;

    int stops = _stopTurns;
    int draws = _drawNumber;
    bool backshoot = false;

    if(_stopTurns<0){
        stopTurns-=1;
        nextPlayer->OnTurn(_stopTurn, _drawCard, _stopTurns, _drawNumber);
        return;
    }
    
    if(!Step(true, _stopTurn, _drawCard, &stops, &draws, &backshoot)){
        if(_stopTurn){
            stopTurns = _stopTurns;
            canStep = false;

            stops = 0;
        }
        else if(_drawCard){
            logger->PushLog(std::to_string(playerId)+";FD <- "+std::to_string(draws));
            for(int i=0; i<_drawNumber; i++){
                DrawCard();
            }
            canStep = false;

            draws = 0;
        }
        else{
            DrawCard();
        }
    }

    while(canStep){
        canStep = Step(false, _stopTurn, _drawCard, &stops, &draws, &backshoot);
    }

    if(stops>0){
        logger->PushLog(std::to_string(playerId)+";S -- "+std::to_string(stops)); 
    }

    if(validator->ValidateEnd(onHand)){
        std::cout<<"winner"<<std::endl;
        logger->PushLog(std::to_string(playerId) + ";W");
        return;
    }
    if(backshoot){
        lastPlayer->OnTurn(stops!=0, draws!=0,stops, draws);
        return;
    }
    else{
        nextPlayer->OnTurn(stops!=0, draws!=0,stops, draws);
        return;
    }
}