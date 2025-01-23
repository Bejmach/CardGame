#ifndef CLIENTPLAYER_H
#define CLIENTPLAYER_H

#include "ClientBase.h"

class ClientPlayer : public ClientBase{
    private:
    
    public:
        void OnTurn() override;
};

#endif