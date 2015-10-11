#include"data_type.h"
#include<cmath>

Var::Var() {
	this->data = 0;
	this->check_real = false;
}

Var::Var(float input) {
	this->data = input;
	this->check_real = true;
}

Var::Var(int input) {
	this->data = (float)input;
	this->check_real = false;
}

void Var::operator=(Var input) {
	this->data = input.data;
	this->check_real = input.check_real;
}

Var Var::operator+(Var input) {
	Var temp;
	long double tempData = this->data + input.data;
	temp.data = (double)tempData;
	temp.check_real = (input.check_real || this->check_real) ? true : false;
	return temp;
}

Var Var::operator-(Var input) {
	Var temp;
	long double tempData = this->data - input.data;
	temp.data = (double)tempData;
	temp.check_real = (input.check_real || this->check_real) ? true : false;
	return temp;
}

Var Var::operator*(Var input) {
	Var temp;
	long double tempData = this->data * input.data;
	temp.data = (double)tempData;
	temp.check_real = (input.check_real || this->check_real) ? true : false;
	return temp;
}

Var Var::operator/(Var input) {
	Var temp;
	long double tempData = this->data / input.data;
	temp.data = (double)tempData;
	temp.check_real = true;
	return temp;
}

Var Var::operator^(Var input) {
	Var temp;
	long double tempData = pow(this->data, input.data);
	temp.data = (double)tempData;
	temp.check_real = (input.check_real || this->check_real) ? true : false;
	return temp;
}

Var Var::var_sin() {
	Var temp;
	long double tempData = sin(this->data);
	temp.data = (double)tempData;
	temp.check_real = this->check_real;
	return temp;
}

Var Var::var_cos() {
	Var temp;
	long double tempData = cos(this->data);
	temp.data = (double)tempData;
	temp.check_real = this->check_real;
	return temp;
}