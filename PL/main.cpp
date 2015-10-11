#include<iostream>
#include<string>
#include"parser.h"

bool run(){
 	std::string input_line;
	std::vector<std::string> command_line;
	
	std::cout<<"start interpreter calculator"<<std::endl
			 <<"input same fomula or commmand"<<std::endl;
	
	getline(std::cin, input_line);

	StringParser line(input_line);
	std::cout<<"success gen"<<std::endl;
	
	command_line = line.parsing();
	for (int i = 0; i < command_line.size(); i++) {
		std::cout << command_line.at(i) << std::endl;
	}
	

	return true;
}

int main(){

	//when run is error or exit, return true 
	while (run());

	std::cout << "Good Bye~!";

 	return 0;
}