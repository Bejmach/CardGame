#ifndef CARDTRANSLATOR_H
#define CARDTRANSLATOR_H

#include "CardTypes.h"
#include "../Other/StringOperations.h"
#include "Card.h"




namespace raw{
	int suit(Suits suit);
	int name(Names name);
}
namespace translate{
	namespace suit{
		std::string Code(Suits suit);
		std::string Codename(Suits suit);
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
	Card str(std::string str);
}

#endif
