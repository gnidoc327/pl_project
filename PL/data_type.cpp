#include"data_type.h"
#include<cmath>

Var::Var() {
	this->data = 0;
	this->check_real = false;
}

Var::Var(double input) {
	this->data = input;
	this->check_real = true;
}

Var::Var(int input) {
	this->data = (double)input;
	this->check_real = false;
}

Var::Var(std::string input) {
	this->data = atof(input.c_str());
	this->check_real = true;
	if (input.find('.') == std::string::npos) this->check_real = false;
	else if (input.compare("e") == 0) this->data = 2.71828182845904523536;
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
	temp.check_real = false;
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

Var Var::var_log() {
	Var temp;
	long double tempData = log(this->data);
	temp.data = (double)tempData;
	temp.check_real = this->check_real;
	return temp;
}

std::ostream& operator<<(std::ostream& os, const Var& var) {
	if (var.check_real) {
		os.setf(std::ios_base::showpoint);
		os << (double)var.data;
	} else {
		os << (int)var.data;
	}
	return os;
}