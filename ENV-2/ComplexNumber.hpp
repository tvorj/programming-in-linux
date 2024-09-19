#pragma once
#include <iostream>
#include <math.h>

class ComplexNumber{

public:
	ComplexNumber(double real_part, double imaginary_part);
	ComplexNumber();
	void set_num(double real_part, double imaginary_part);
	void show();
	std::size_t abs_val();
	ComplexNumber operator+(const ComplexNumber& other);
	ComplexNumber operator-(const ComplexNumber& other);
	ComplexNumber operator*(double cvalue);
	

private:
	double rpart;//real part
	double impart;//imaginary part

};

