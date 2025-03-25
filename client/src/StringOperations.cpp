#include "../include/StringOperations.h"

#include <algorithm>
#include <cctype>

std::vector<std::string> SO::Split(std::string str, std::string delimiter){
	std::string pushed;

	std::vector<std::string> holder;
		int startPosition = 0;
		int endPosition = str.find(delimiter);
		while(endPosition!=std::string::npos){
			endPosition = endPosition+startPosition;
			pushed = str.substr(startPosition, endPosition-startPosition);
			if(pushed!=""){
				holder.push_back(str.substr(startPosition, endPosition-startPosition));
			}
			startPosition = endPosition+1;
			if(startPosition>=str.length()){
				return holder;
			}
			endPosition = str.substr(startPosition).find(delimiter);
		}
	pushed = str.substr(startPosition, endPosition-startPosition);
	if(pushed!=""){
		holder.push_back(str.substr(startPosition, endPosition-startPosition));
	}
	return holder;
}
std::string SO::Merge(std::vector<std::string> vec, std::string delimiter, int skipFront, int skipEnd){
	std::string returner;
	if(skipFront+skipEnd < vec.size()-1 && skipFront>=0 && skipEnd>=0){
		for(int i=skipFront; i<vec.size()-skipEnd; i++){
			returner += (i==skipFront) ? vec[i] : delimiter+vec[i];
		}
	}
	return returner;
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
