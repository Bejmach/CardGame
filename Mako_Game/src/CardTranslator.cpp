#include "CardTranslator.h"
#include "CardTypes.h"

int translate::raw::Suit(Suits suit){
	return static_cast<int>(suit);
}

int translate::raw::Name(Names name){
	return static_cast<int>(name);
}

std::string translate::suit::Code(Suits suit){
	return SuitsCode[static_cast<int>(suit)];
}
std::string translate::suit::Codename(Suits suit){
	return SuitsCodename[static_cast<int>(suit)];
}
std::string translate::suit::EN(Suits suit){
	return SuitsEN[static_cast<int>(suit)];
}
std::string translate::suit::PL(Suits suit){
	return SuitsPL[static_cast<int>(suit)];
}
std::string translate::suit::Id(int id){
	return SuitsCodename[id];
}

std::string translate::name::Code(Names name){
	return NamesCode[static_cast<int>(name)];
}
std::string translate::name::EN(Names name){
	return NamesEN[static_cast<int>(name)];
}
std::string translate::name::PL(Names name){
	return NamesPL[static_cast<int>(name)];
}
std::string translate::name::Id(int id){
	return NamesCode[id];
}

Card decode::Str(std::string str){
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

Suits decode::intiger::Suit(int suitCode){
	return static_cast<Suits>(suitCode);
}
Names decode::intiger::Name(int nameCode){
	return static_cast<Names>(nameCode);
}
