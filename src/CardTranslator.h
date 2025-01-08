#ifndef CARDTRANSLATOR_H
#define CARDTRANSLATOR_H

#include "CardTypes.h"

namespace raw{
	namespace suit{
		int EN(Suits suit);
		int PL(Suits suit);
	}
	namespace name{
		int EN(Names name);
		int PL(Names name);
	}
}
namespace translate{
	namespace suit{
		std::string EN(Suits suit);
		std::string PL(Suits suit);
	}
	namespace name{
		std::string EN(Names name);
		std::string PL(Names name);
	}
}

#endif
