#ifndef CLIENTBOT_H
#define CLIENTBOT_H

#include "ClientBase.h"

class ClientBot : public ClientBase{
    private:

    public:
        ClientBot(Deck* _deck = nullptr, Validator* _validator = nullptr);
        ~ClientBot() override {};

        void OnTurn() override;
        bool Step(bool first);
};

#endif