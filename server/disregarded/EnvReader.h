#ifndef ENVREADER_H
#define ENVREADER_H

#include <iostream>
#include <vector>
#include <utility>

#include <fstream>
#include <string>

class EnvReader{
	private:
		std::vector<std::pair<std::string, std::string>> values;

		std::string path;
		std::pair<std::string, std::string> FormatLine(std::string line);

	public:
		EnvReader(std::string _path = "");
		void ReadFile();

		std::string GetData(std::string key);
};

#endif
