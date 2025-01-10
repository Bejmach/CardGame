#include "StringOperations.h"

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
