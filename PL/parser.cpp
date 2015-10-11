#include"parser.h"

StringParser::StringParser(std::string input){
	this->data = input;
	
}

std::vector<std::string> StringParser::parsing(){
	std::string temp_line = this->data;
	std::vector<std::string> result;
	std::string temp_string;

	int pos = 0;

	while ((pos = temp_line.find('(')) != std::string::npos) {
		temp_line.erase(temp_line.begin() + pos);
	}

	pos = 0;
	while ((pos = temp_line.find(')')) != std::string::npos) {
		temp_line.erase(temp_line.begin() + pos);
	}

	pos = 0;
	while ((pos = temp_line.find(' ')) != std::string::npos) {
		temp_string = temp_line.substr(0, pos);
		result.push_back(temp_string);
		temp_line.erase(0, pos + 1);
	}
	result.push_back(temp_line);

	return result;
}