#include"parser.h"
#include<iostream>

StringParser::StringParser(std::string input){
	this->data = input;
}

std::vector<std::string> StringParser::parsing(){
	std::string temp_line = this->data;
	std::vector<std::string> result;
	std::string temp_string;

	int pos = 0;
	int countParenthesis = 1;

	//check command
	if (temp_line.at(0) != '(') {
		result.push_back(this->data);
		return result;
	}

	//calc part no command
	temp_line.erase(temp_line.begin());
	temp_line.erase(temp_line.end() - 1);
	pos = temp_line.find(' ') + 1;
		
	//check inner calc
	while (pos < temp_line.length()) {
		if (temp_line.at(pos) == '(') {
			//calc
			pos = temp_line.find(' ');
			temp_string = temp_line.substr(0, pos);
			temp_line.erase(0, pos+1);
			result.push_back(temp_string);

			//parameter1
			pos = 0;
			countParenthesis = 0;
			while (pos < temp_line.length()) {
				if (temp_line.at(pos) == '(') countParenthesis++;
				if (temp_line.at(pos) == ')') countParenthesis--;
				if (countParenthesis == 0) break;
				pos++;
			}

			if (pos == 0) {
				pos = temp_line.find(' ');
				temp_string = temp_line.substr(0, pos);
				temp_line.erase(0, pos+1);
			} else {
				temp_string = temp_line.substr(0, pos+1);
				temp_line.erase(0, pos+2);
			}
			result.push_back(temp_string);

			//parameter2
			if (!temp_line.empty()) {
				result.push_back(temp_line);
			}
			
			for (int i = 0; i < result.size(); i++)
				std::cout << result.at(i) << std::endl;
			return result;
		} 
		pos++;
	}

	//not exist inner calc
	pos = 0;
	while ((pos = temp_line.find(' ')) != std::string::npos) {
		temp_string = temp_line.substr(0, pos);
		result.push_back(temp_string);
		temp_line.erase(0, pos + 1);
	}
	result.push_back(temp_line);

	for (int i = 0; i < result.size(); i++)
		std::cout << result.at(i) << std::endl;

	return result;
}