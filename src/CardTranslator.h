#ifndef CARDTRANSLATOR_H
#define CARDTRANSLATOR_H

#include "CardTypes.h"
#include "StringOperations.h"
#include "Card.h"




namespace raw{
	int suit(Suits suit);
	int name(Names name);
}
namespace translate{
	namespace suit{
		std::string Code(Suits suit);
		std::string EN(Suits suit);
		std::string PL(Suits suit);
	}
	namespace name{
		std::string Code(Names name);
		std::string EN(Names name);
		std::string PL(Names name);
	}
}
namespace decode{
	Card string(std::string str){
		std::vector<std::string> formated = SO::Split(str, ";");
		for(int i=0; i<formated.size(); i++){
			formated[i] = SO::ToUpper(formated[i]);
		}

		Suits suit = Suits::Undefined;
		Names name = Names::Undefined;

		for(int i=0; i<formated.size(); i++){
			if(formated[i] == "2"){name = Names::Two;}
			else if(formated[i] == "3"){name = Names::Three;}
			else if(formated[i] == "4"){name = Names::Four;}
			else if(formated[i] == "5"){name = Names::Five;}
			else if(formated[i] == "6"){name = Names::Six;}
			else if(formated[i] == "7"){name = Names::Seven;}
			else if(formated[i] == "8"){name = Names::Eight;}
			else if(formated[i] == "9"){name = Names::Nine;}
			else if(formated[i] == "10"){name = Names::Ten;}
			else if(formated[i] == "J"){name = Names::Jack;}
			else if(formated[i] == "Q"){name = Names::Queen;}
			else if(formated[i] == "K"){name = Names::King;}
			else if(formated[i] == "A"){name = Names::Ace;}
			
			else if(formated[i] == "H"){suit = Suits::Heart;}
			else if(formated[i] == "C"){suit = Suits::Club;}
			else if(formated[i] == "D"){suit = Suits::Diamond;}
			else if(formated[i] == "S"){suit = Suits::Spade;}

		}

		Card card = Card(suit, name);

		return card;
	}
}

#endif
