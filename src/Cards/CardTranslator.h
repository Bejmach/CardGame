#ifndef CARDTRANSLATOR_H
#define CARDTRANSLATOR_H

#include "CardTypes.h"
#include "../Other/StringOperations.h"
#include "Card.h"





namespace translate{
	namespace suit{
		std::string Code(Suits suit);
		std::string Codename(Suits suit);
		std::string EN(Suits suit);
		std::string PL(Suits suit);
		std::string Id(int id);
	}
	namespace name{
		std::string Code(Names name);
		std::string EN(Names name);
		std::string PL(Names name);
		std::string Id(int id);
	}
	namespace raw{
		int Suit(Suits suit);
		int Name(Names name);
	}
}
namespace decode{
	Card Str(std::string str);

	namespace intiger{
		Suits Suit(int suitCode);
		Names Name(int nameCode);
	}
}

#endif
