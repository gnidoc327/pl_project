#ifndef PARSER_H
#define PARSER_H

#include<vector>
#include<string>

class StringParser{
private:
	std::string data;  

public:
	std::vector<std::string> parsing();
	StringParser(std::string);
};

#endif /* !PARSER_H */
