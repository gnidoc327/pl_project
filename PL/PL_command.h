#ifndef OPERATOR_H
#define OPERATOR_H

#include"data_type.h"
#include"parser.h"
#include<vector>
#include<iostream>
#include<stdlib.h>
#include<io.h> 
#include<fstream>

#define COMMAND_NUM 10
#define CALC_NUM 9
#define M_E 2.71828182845904523536

typedef struct _finddata_t  FILE_SEARCH;

class PL_command{
private:
	std::string command;
	std::vector<std::string> parameter;

	bool operate_command(int);
	int check_calc(std::string);
	Var operate_calc(int, Var, Var);
	Var operate_calc(int, Var);
	bool check_inner_command(std::string);

public:
	PL_command(std::vector<std::string>);
	PL_command(std::vector<std::string>, std::vector<list_name>, std::vector<list_name>);
	Var operate();
	int check_command(std::string);
	std::vector<list_name> var_list;
	std::vector<list_name> formula_list;

private:
	std::string command_list[COMMAND_NUM]{
		{"clear"},
		{"reset"},
		{"list"},
		{"save_formula"},
		{"load_formula"},
		{"load_formulaTofile"},
		{"ls"},
		{"exit"},
		{"help"},
		{"about"}
	};

	std::string calc_list[CALC_NUM]{
		{"equ"},
		{"add"},
		{"sub"},
		{"mul"},
		{"div"},
		{"pow"},
		{"ln"},
		{"sin"},
		{"cos"},
	};
};

#endif /* !OPERATOR_H */
