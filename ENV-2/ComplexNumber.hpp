#pragma once
#include <iostream>
#include <math.h>

class ComplexNumber{

public:
	ComplexNumber(double real_part, double imaginary_part);
	std::size_t abs_val();
	ComplexNumber operator+(const ComplexNumber& other);
	ComplexNumber operator-(const ComplexNumber& other);
	ComplexNumber operator*(double cvalue);
	

private:
	double rpart;//real part
	double impart;//imaginary part

};

