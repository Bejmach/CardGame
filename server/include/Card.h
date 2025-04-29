#ifndef CARD_H
#define CARD_H

#include "CardTypes.h"
#include <string>

class Card{
	private:
		Suits suit;
		Names name;
	
	public:
		Card(Suits _suit, Names _name);
		Card(int _suit = 0, int _name = 0);

		Suits GetSuit();
		Names GetName();

		int GetRawSuit();
		int GetRawName();
};


#endif
