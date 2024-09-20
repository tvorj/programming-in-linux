#pragma once
#include <iostream>
#include <math.h>

class ComplexNumber{

public:
	ComplexNumber(double real_part = 0, double imaginary_part = 0);
	void set_num(double real_part, double imaginary_part);
	friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& obj);
	double abs_val()const;
	ComplexNumber operator+(const ComplexNumber& other)const;
	ComplexNumber operator-(const ComplexNumber& other)const;
	ComplexNumber operator*(double cvalue)const;
	

private:
	double rpart;//real part
	double impart;//imaginary part

};

