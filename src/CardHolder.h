#ifndef CARDHOLDER_H
#define CARDHOLDER_H

#include "Card.h"

class CardHolder{
	public:
		CardHolder();
		~CardHolder();
		
		Card** cardList;

		void Allocate();
		void Deallocate();
};

#endif
