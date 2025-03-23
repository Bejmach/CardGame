#ifndef CLIENTBOT_H
#define CLIENTBOT_H

#include "ClientBase.h"

class ClientBot : public ClientBase{
    protected:
        int stopTurns = 0;
        int drawNumber = 0;

    public:
        ClientBot(Deck* _deck = nullptr, Validator* _validator = nullptr);
        ~ClientBot() override {};

        void OnTurn(bool _stopTurn, bool _drawCard, int _stopTurns, int _drawNumber) override;
        void ChangeCard(std::vector<bool>) override;
        bool Step(bool first, bool _stopTurn, bool _drawCard, int *stops, int *draws, bool *backshoot);
};

#endif