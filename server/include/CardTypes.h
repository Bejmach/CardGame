#ifndef CARDTYPES_H
#define CARDTYPES_H

#include <iostream>
#include <vector>

enum class Suits{Heart, Diamond, Club, Spade, Undefined};
enum class Names{Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace, Undefined};

extern std::vector<std::string> SuitsCode;
extern std::vector<std::string> SuitsCodename;
extern std::vector<std::string> SuitsEN;
extern std::vector<std::string> SuitsPL;

extern std::vector<std::string> NamesCode;
extern std::vector<std::string> NamesEN;
extern std::vector<std::string> NamesPL;

#endif
