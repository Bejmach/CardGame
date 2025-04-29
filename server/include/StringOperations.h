#ifndef STRINGOPERATIONS_H
#define STRINGOPERATIONS_H

#include <iostream>
#include <vector>
#include <string>

namespace SO{
	std::vector<std::string> Split(std::string str, std::string delimiter);
	std::string ToLower(std::string str);
	std::string ToUpper(std::string str);
	bool Numeric(std::string str);
}

#endif
