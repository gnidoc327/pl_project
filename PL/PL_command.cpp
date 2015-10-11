#include"PL_command.h"

PL_command::PL_command(std::vector<std::string> input) {
	int size = input.size();
	this->command = input.at(0);
	input.erase(input.begin());
	if(size != 1) this->parameter = input;	
}

PL_command::PL_command(std::vector<std::string> input_line, std::vector<list_name> super_var_list, std::vector<list_name> super_formula_list) {
	int size = input_line.size();
	this->command = input_line.at(0);
	input_line.erase(input_line.begin());
	if (size != 1) this->parameter = input_line;
	this->var_list = super_var_list;
	this->formula_list = super_formula_list;
}

Var PL_command::operate() {
	int index = -1;
	Var tempVar1;
	Var tempVar2;

	if((index = check_command(this->command)) != -1){
		return this->operate_command(index);
	} else if ((index = check_calc(this->command)) != -1) {
		//check parameter1 inner calc
		if (check_inner_command(parameter.at(0))) {
			StringParser inner_line(parameter.at(0));
			PL_command inner_command(inner_line.parsing(),this->var_list, this->formula_list);
			tempVar1 = inner_command.operate();
		} else {
			Var temp1(parameter.at(0));
			tempVar1 = temp1;
		}
		//check parameter2 inner calc
		if ((parameter.size() == 2)) {
			if (check_inner_command(parameter.at(1))) {
				StringParser inner_line(parameter.at(1));
				PL_command inner_command(inner_line.parsing(), this->var_list, this->formula_list);
				tempVar2 = inner_command.operate();
			} else {
				Var temp2(parameter.at(1));
				tempVar2 = temp2;
			}
			return operate_calc(index, tempVar1, tempVar2);
		} else {
			return operate_calc(index, tempVar1);
		}
	} else {
		std::cout<<"\'"<< this->command << "\' is not command! Type \'help\' and reading help" << std::endl;
	}

	return true;
}
Var PL_command::operate_calc(int index, Var var) {
	Var result;
	for (size_t i = 0; i < var_list.size(); i++) {
		if (parameter.at(0).compare(var_list.at(i).name) == 0) {
			Var tempVar(var_list.at(i).data);
			var = tempVar;
		}
	}
	switch (index) {
		case 5: //pow
		{
			Var temp(atof(parameter.at(1).c_str()));
			result = var^temp;
			break;
		}
		case 6: //ln
			result = var.var_log();
			break;
		case 7: //sin
			result = var.var_sin();
			break;
		case 8://cos
			result = var.var_cos();
			break;
		default:
			std::cout << "operator index error" << std::endl;
	}
	return result;
}

Var PL_command::operate_calc(int index, Var var1, Var var2) {
	Var result;
	for (size_t i = 0; i < var_list.size(); i++) {
		if (parameter.at(0).compare(var_list.at(i).name) == 0) {
			Var tempVar(var_list.at(i).data);
			var1 = tempVar;
		}
		if (parameter.at(1).compare(var_list.at(i).name) == 0) {
			Var tempVar(var_list.at(i).data);
			var1 = tempVar;
		}
	}

	switch (index) {
		case 0: //equ
		{
			list_name temp;
			temp.name = parameter.at(0);
			temp.data = parameter.at(1);
			var_list.push_back(temp);
			result = var2;
		}
		break;
		case 1: //add
			result = var1 + var2;
			break;
		case 2: //sub
			result = var1 - var2;
			break;
		case 3: //mul
			result = var1 * var2;
			break;
		case 4: //div
			result = var1 / var2;
			break;
		default:
			std::cout << "operator index error" << std::endl;
	}
	return result;
}
bool PL_command::operate_command(int index) {
	switch (index) {
	case 0: //clear
		for (int i = 0; i < 50; i++)
			std::cout << std::endl;
		break;
	case 1: //list_reset
		this->var_list.clear();
		this->formula_list.clear();
		break;
	case 2: //var_list
		std::cout << "Value List" << std::endl;
		if (var_list.size() == 0)
			std::cout << "value list not exist." << std::endl;
		else
			for (size_t i = 0; i < var_list.size(); i++)
				std::cout << var_list.at(0).name << " = " << var_list.at(0).data << std::endl;

		std::cout << "Formula List" << std::endl;
		if (formula_list.size() == 0)
			std::cout << "formula list not exist." << std::endl;
		else
			for (size_t i = 0; i < formula_list.size(); i++)
				std::cout << formula_list.at(0).name << " = " << formula_list.at(0).data << std::endl;

		break;
	case 3: //save_formula
	{
		list_name temp_list;
		if (parameter.size() != 2)
			std::cout << "parameter empty" << std::endl;
		temp_list.name = parameter.at(0);
		temp_list.data = parameter.at(1);

		this->formula_list.push_back(temp_list);
		std::cout << temp_list.name << " = " << temp_list.data << " is save!!" << std::endl;
		break;
	}
	case 4: //load_formula
	{
		for (size_t i = 0; i < formula_list.size(); i++) {
			if (formula_list.at(i).name.compare(parameter.at(0)) == 0) {
				StringParser load_line(formula_list.at(i).data);
				std::vector<std::string> load_command_line = load_line.parsing();
				PL_command child_command_operator(load_command_line, this->var_list, this->formula_list);
				std::cout << child_command_operator.operate() << std::endl;
				this->var_list = child_command_operator.var_list;
				this->formula_list = child_command_operator.formula_list;
			}
		}
		break;
	}
	case 5: //load_formulaTofile
	{
		list_name temp;
		char line_file[128];
		int i, j;
		std::ifstream file(parameter.at(0));
		file.getline(line_file, 128);
		for (i = 0; i < 128; i++)
			if (line_file[i] == ' ')
				break;

		for (j = i; j < 128; j++)
			if (line_file[j] == '\0')
				break;
		temp.name = std::string(line_file, 0, i);
		temp.data = std::string(line_file, i + 2, j);
		formula_list.push_back(temp);
		break;
	}
	case 6: //file_list
		long h_file;
		char search_Path[128];

		FILE_SEARCH file_search;

		sprintf_s(search_Path, ".\\*.*");
		if ((h_file = _findfirst(search_Path, &file_search)) == -1L) {
			std::cout << "No files in current directory!" << std::endl;
		}
		else {
			do {
				std::cout << file_search.name << std::endl;
			} while (_findnext(h_file, &file_search) == 0);
			_findclose(h_file);
		}
		break;
	case 7: //calc_exit
		std::cout << "Good Bye~!" << std::endl
			<< "Exit Calculator" << std::endl;
		exit(EXIT_SUCCESS);
		break;
	case 8: //help
		std::cout << "May I help you?" << std::endl<<std::endl
			<< "instruction set list" << std::endl
			<< "clear : screen clear" << std::endl
			<< "reset : value list reset" << std::endl
			<< "list : show value, formula list" << std::endl
			<< "save_formula : formula is save to list" << std::endl
			<< "load_formula : formula is load from list" << std::endl
			<< "load_formulaTofile : formula is load to file, and save to list" << std::endl
			<< "ls : show directory file list" << std::endl
			<< "exit : exit program" << std::endl
			<< "help : this page" << std::endl
			<< "about : who make this program, and some info" << std::endl << std::endl
			<< "calculator operator set list" << std::endl
			<< "equ -> (equ a 3) ==> a=3" << std::endl
			<< "add -> (add 1 2) = 3" << std::endl
			<< "sub -> (add 2 1) = 1" << std::endl
			<< "mul -> (mul 3 2) = 6 " << std::endl
			<< "div -> (div 4 2) = 2" << std::endl
			<< "pow -> (pow 3 3) = 27, you can use real number to second parameter, e to first parameter" << std::endl
			<< "ln -> (ln 3) = ln3" << std::endl
			<< "sin -> (sin 90) = 1" << std::endl
			<< "cos -> (cos 90) = 0" << std::endl;
		break;
	case 9: //about
		std::cout << "This is Calculator" << std::endl
			<< "Made by Kim han sung in CAUCSE" << std::endl
			<< "It was made becaucse Programming Language Project." << std::endl;
		break;
	default:
		return false;
	}
	return true;
}

int PL_command::check_command(std::string input) {
	for (int i = 0; i < COMMAND_NUM; i++)
		if (input.compare(command_list[i]) == 0) return i;
	return -1;
}

int PL_command::check_calc(std::string input) {
	for (int i = 0; i < CALC_NUM; i++)
		if (input.compare(calc_list[i]) == 0) return i;
	return -1;
}

bool PL_command::check_inner_command(std::string input) {
	if (input.at(0) == '(') return true;
	return false;
}