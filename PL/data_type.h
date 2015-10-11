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
	void operator=(Var);
	Var operator+(Var);
	Var operator-(Var);
	Var operator*(Var);
	Var operator/(Var);
	Var operator^(Var);
	Var var_sin();
	Var var_cos();
};


#endif /* !DATA_TYPE_H */
