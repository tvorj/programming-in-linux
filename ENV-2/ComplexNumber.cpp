#include "ComplexNumber.hpp"

ComplexNumber::ComplexNumber(double real_part, double imaginary_part ): rpart(real_part), impart(imaginary_part){}

ComplexNumber::ComplexNumber():rpart(0), impart(0){}

void ComplexNumber::set_num(double real_part, double imaginary_part){
	rpart = real_part;
	impart = imaginary_part;
}

void ComplexNumber::show(){
	if(impart >= 0){
		std::cout<<rpart<<"+"<<impart<<"*i";
	}
	else{
		std::cout<<rpart<<impart<<"*i";
	}
}

std::size_t ComplexNumber::abs_val(){
	return sqrt(pow(rpart,2) + pow(impart,2));
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber& other){
	ComplexNumber temp(rpart + other.rpart, impart + other.impart);
	return temp;
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber& other){
	ComplexNumber temp(rpart - other.rpart, impart - other.impart);
	return temp;
}

ComplexNumber ComplexNumber::operator*(double cvalue){
	ComplexNumber temp(rpart * cvalue, impart * cvalue);
	return temp;
}
