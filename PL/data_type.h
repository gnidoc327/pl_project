#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include<stdbool.h>
#include<string>

class Var {
private:
	double data;
	bool check_real;
public:
	Var();
	Var(double);
	Var(int);
	Var(std::string);
	void operator=(Var);
	Var operator+(Var);
	Var operator-(Var);
	Var operator*(Var);
	Var operator/(Var);
	Var operator^(Var);
	Var var_sin();
	Var var_cos();
	Var var_log();
	friend std::ostream& operator<<(std::ostream& os, const Var& var);
};

struct list_name {
	std::string name;
	std::string data;
};

#endif /* !DATA_TYPE_H */
