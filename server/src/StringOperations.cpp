#include "../include/StringOperations.h"

#include <algorithm>
#include <cctype>

std::vector<std::string> SO::Split(std::string str, std::string delimiter){
	std::vector<std::string> holder;
		int startPosition = 0;
		int endPosition = str.find(delimiter);
		while(endPosition!=std::string::npos){
			endPosition = endPosition+startPosition;
			holder.push_back(str.substr(startPosition, endPosition-startPosition));
			startPosition = endPosition+1;
			if(startPosition>=str.length()){
				holder.push_back("");
				return holder;
			}
			endPosition = str.substr(startPosition).find(delimiter);
		}
	holder.push_back(str.substr(startPosition, endPosition-startPosition));
	return holder;
}

std::string SO::ToLower(std::string str){
	std::transform(str.begin(), str.end(), str.begin(),
			[](unsigned char c){return std::tolower(c); });

	return str;
}
std::string SO::ToUpper(std::string str){
	std::transform(str.begin(), str.end(), str.begin(),
			[](unsigned char c){return std::toupper(c); });

	return str;
}
bool SO::Numeric(std::string str){
	return (std::to_string(std::stoi(str)) == str);
}
