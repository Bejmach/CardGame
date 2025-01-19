#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include <iostream>
#include <vector>

#include "Card.h"
#include "CardTranslator.h"
#include "Deck.h"

class PlayerClient{
	protected:
		bool skipTurn = false;
		int turnsSkipped = 0;

		std::vector<Card*> onHand;
		Deck* deck;

		PlayerClient* lastPlayer;
		PlayerClient* nextPlayer;

	public:
		virtual void OnTurn() = 0;

		PlayerClient(Deck* _deck = nullptr);

		void SetDeck(Deck* _deck);

		void PrintCard(int id);
		void PrintHand();

		Card* GetCard(int id);
		void DrawCard();
		void PlayCard(int id);

		int HandSize();

		void SkipTurn(int howLong);

		void SetLastPlayer(PlayerClient* player);
		void SetNextPlayer(PlayerClient* player);

};

#endif
