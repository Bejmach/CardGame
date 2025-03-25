#ifndef CLIENTBASE_H
#define CLIENTBASE_H

#include "ClientBase.h"


class ClientWeb : public ClientBase{
	protected:

	public:
		ClientWeb(Deck* _deck = nullptr, Validator* _validator = nullptr);
        ~ClientWeb() override {};

        void OnTurn(bool _stopTurn, bool _drawCard, int _stopTurns, int _drawNumber) override;
        void ChangeCard(std::vector<bool>) override;
};

#endif
