#include "CardTranslator.h"

int raw::suit::EN(Suits suit){
	return static_cast<int>(suit);
}
int raw::suit::PL(Suits suit){
	return static_cast<int>(suit);
}
int raw::name::EN(Names name){
	return static_cast<int>(name);
}
int raw::name::PL(Names name){
	return static_cast<int>(name);
}
std::string translate::suit::EN(Suits suit){
	return SuitsEN[static_cast<int>(suit)];
}
std::string translate::suit::PL(Suits suit){
	return SuitsPL[static_cast<int>(suit)];
}
std::string translate::name::EN(Names name){
	return NamesEN[static_cast<int>(name)];
}
std::string translate::name::PL(Names name){
	return NamesPL[static_cast<int>(name)];
}

