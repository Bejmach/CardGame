#ifndef CLIENTPLAYER_H
#define CLIENTPLAYER_H

#include "ClientBase.h"

class ClientPlayer : public ClientBase{
    private:
        int stopTurns = 0;
        int drawNumber = 0;
    
    public:
        ClientPlayer(Deck* _deck = nullptr, Validator* _validator = nullptr);
        ~ClientPlayer() override {};

        void OnTurn(bool _stopTurn, bool _drawCard, int _stopTurns, int _drawNumber) override;
        void ChangeCard(std::vector<bool>) override;
        bool Step(bool first, bool _stopTurn, bool _drawCard, int *stops, int *draws, bool *backshoot);

        void DrawGameStatus();
};

#endif