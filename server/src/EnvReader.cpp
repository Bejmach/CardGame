#include "../include/EnvReader.h"

EnvReader::EnvReader(std::string _path){
	path = _path;

	if(path!=""){
		ReadFile();
	}
}

void EnvReader::ReadFile(){
	values.clear();
	
	if(path == ""){
		return;
	}
	std::ifstream file(path);

	if(!file.is_open()){
		return;
	}

	std::string line;
	while(getline(file, line)){
		values.push_back(FormatLine(line));
	}
	file.close();
}

std::pair<std::string, std::string> EnvReader::FormatLine(std::string line){
	int delimiterPosition = line.find("=");

	return {line.substr(0, delimiterPosition), line.substr(delimiterPosition+1, line.length())};
}

std::string EnvReader::GetData(std::string key){
	for(int i=0; i<values.size(); i++){
		if(values[i].first == key){
			return values[i].second;
		}
	}
	return "";
}
