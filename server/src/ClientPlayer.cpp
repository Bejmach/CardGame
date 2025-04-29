#include "../include/ClientPlayer.h"

ClientPlayer::ClientPlayer(Deck* _deck, Validator* _validator){
    this->deck = _deck;
    this->validator = _validator;
}

bool ClientPlayer::Step(bool first, bool _stopTurn, bool _drawCard, int *stops, int *draws, bool* backshoot){

    bool suit = true;
    bool name = true;

    if(!first){
        suit = false;
    }

    if(_stopTurn){
        suit = false;
    }

    std::vector<int> cardValues = validator->CardValues(onHand, suit, name, {*draws!=0});

    int highest = 0;

    for(int i=0; i<cardValues.size(); i++){
        if(cardValues[i]>highest){
            highest = cardValues[i];
        }
    }

    if(first){
        DrawGameStatus();
    }
    else if(highest!=0){
        DrawGameStatus();
    }

    if(highest == 0){
        if(first){
            if(*draws!=0){
                std::cout<<"Can't make any move. Forced to draw "<<*draws<<" cards"<<std::endl;
            }
            if(*stops!=0){
                std::cout<<"Can't make any move. Forced to stun for "<<*stops<<" turns"<<std::endl;
            }
            else{
                std::cout<<"Can't make any move. Forced to draw"<<std::endl;
            }
        }
        return false;
    }

    else{

        int id;
        std::string idStr;
        std::cout<<"play card by id: ";
        std::cin>>idStr;

        while(true){
            if(SO::Numeric(idStr)){
                id = std::stoi(idStr)-1;
                if(id<0 || id>=onHand.size()){
                    std::cout<<"wrong id, choose again: ";
                    std::cin>>idStr;
                }
                else{
                    if(cardValues[id]<=0){
                        std::cout<<"move not possible, choose again: ";
                        std::cin>>idStr;
                    }
                    else{
                        break;
                    }
                }
            }
            else{
                std::cout<<"id not numeric, choose again: ";
                std::cin>>idStr;
            }
        }

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
    return false;
}

void ClientPlayer::ChangeCard(std::vector<bool> actions){
    if(actions[0]){

        std::string suitStr;
        std::cout<<"Select suit(H/D/S/C): ";
        std::cin>>suitStr;
        while(true){
            if(decode::Str(suitStr).GetSuit()==Suits::Undefined){
                std::cout<<"Wrong suit(H/D/S/C): ";
                std::cin>>suitStr;
            }
            else{
                rules->CommandUpdate(SO::ToUpper(suitStr));
                break;
            }
        }
    }
    else if(actions[1]){

        std::string nameStr;
        std::cout<<"Select name(2/3/../J/Q/K/A): ";
        std::cin>>nameStr;
        while(true){
            if(decode::Str(nameStr).GetName()==Names::Undefined){
                std::cout<<"Wrong name(2/3/../J/Q/K/A): ";
                std::cin>>nameStr;
            }
            else{
                rules->CommandUpdate(SO::ToUpper(nameStr));
                break;
            }
        }
    }
}

void ClientPlayer::OnTurn(bool _stopTurn, bool _drawCard, int _stopTurns, int _drawNumber){
    bool canStep = true;

    int stops = _stopTurns;
    int draws = _drawNumber;
    bool backshoot = false;

    if(stopTurns>0){
        logger->PushLog(std::to_string(playerId)+";S -- "+std::to_string(stopTurns));
        nextPlayer->OnTurn(_stopTurn, _drawCard, _stopTurns, _drawNumber);
        stopTurns -= 1;
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
                if(!DrawCard()){
                    return;
                };
            }
            canStep = false;

            draws = 0;
        }
        else{
            if(!DrawCard()){
                return;
            };
        }
    }

    while(canStep){
        canStep = Step(false, _stopTurn, _drawCard, &stops, &draws, &backshoot);
    }

    if(stops>0){
        logger->PushLog(std::to_string(playerId)+";S -> "+std::to_string(stops)); 
    }

    if(validator->ValidateEnd(onHand)){
        std::cout<<"winner"<<std::endl;
        logger->PushLog(std::to_string(playerId) + ";W");
        return;
    }
    if(backshoot){
        lastPlayer->OnTurn(stops!=0, draws!=0,stops, draws);
    }
    else{
        nextPlayer->OnTurn(stops!=0, draws!=0,stops, draws);
    }
}

void ClientPlayer::DrawGameStatus(){
    if(stopTurns>0){
        std::cout<<"Turn skipped, you are stopped"<<std::endl;
    }
    else{
        if(rules->GetData()[0] != 13){
            std::cout<<"Current forced card: "<<translate::name::EN(decode::intiger::Name(rules->GetData()[0]))<<std::endl;
        }
        else if(rules->GetData()[1] != 4){
            std::cout<<"Current forced card: "<<translate::suit::EN(decode::intiger::Suit(rules->GetData()[1]))<<std::endl;
        }
        else{
            std::cout<<"Current used card: "<<translate::name::EN(deck->GetLastUsed()->GetName())<<" of "<<translate::suit::EN(deck->GetLastUsed()->GetSuit())<<std::endl<<std::endl;
        }
        std::cout<<"Select card to play"<<std::endl;
        for(int i=0; i<onHand.size(); i++){
            std::cout<<"    "<<i+1<<": "<<translate::name::EN(onHand[i]->GetName())<<" of "<<translate::suit::EN(onHand[i]->GetSuit())<<std::endl;
        }
    }
}
