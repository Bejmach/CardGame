#ifndef CLIENTPLAYER_H
#define CLIENTPLAYER_H

#include "ClientBase.h"

class ClientPlayer : public ClientBase{
    private:
    
    public:
        void OnTurn(bool _stopTurn, bool _drawCard, int _stopTurns, int _drawNumber) override;
};

#endif