#include<iostream>
#include<string>
#include<vector>
#include"PL_command.h"
#include"data_type.h"
#include"parser.h"



std::vector<list_name> var_list;
std::vector<list_name> formula_list;

bool run(){
	Var result;
 	std::string input_line;
	std::vector<std::string> command_line;
	
	std::cout<<std::endl
			 <<"PL_Calc >> ";
	
	getline(std::cin, input_line);

	StringParser line(input_line);
	command_line = line.parsing();
	PL_command command_operator(command_line, var_list, formula_list);
	var_list.clear();
	formula_list.clear();
	if (command_operator.check_command(command_line.at(0)) == -1)
		std::cout << command_operator.operate() << std::endl;
	else
		command_operator.operate();
	var_list = command_operator.var_list;
	formula_list = command_operator.formula_list;
	return true;
}

int main(){

	//when run is error or exit, return true 
	std::cout << "start interpreter calculator" << std::endl
			  <<"input same fomula or commmand" << std::endl;
	while (run());

	std::cout << "Calculator is error. Exit shell";

 	return 0;
}