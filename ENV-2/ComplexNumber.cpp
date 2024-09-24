#include "ComplexNumber.hpp"

//ComplexNumber constructor
ComplexNumber::ComplexNumber(double real_part, double imaginary_part ): rpart(real_part), impart(imaginary_part){}

//set ComplexNumber manually
void ComplexNumber::set_num(double real_part, double imaginary_part){
	rpart = real_part;
	impart = imaginary_part;
}

//overload operator<< for ComlpexNumber
std::ostream& operator<<(std::ostream& os, const ComplexNumber& obj){
	os<< obj.rpart << " + " << obj.impart<<" * i"<<std::endl;
	return os;
}

//calculate absolute value
double ComplexNumber::abs_val()const{
	return sqrt(pow(rpart,2) + pow(impart,2));
}

//overload operator+ for ComplexNumber
ComplexNumber ComplexNumber::operator+(const ComplexNumber& other)const{
	ComplexNumber temp(rpart + other.rpart, impart + other.impart);
	return temp;
}

//overload operator- for ComplexNumber
ComplexNumber ComplexNumber::operator-(const ComplexNumber& other)const{
	ComplexNumber temp(rpart - other.rpart, impart - other.impart);
	return temp;
}

//overload operator* for ComplexNumber
ComplexNumber ComplexNumber::operator*(double cvalue)const{
	ComplexNumber temp(rpart * cvalue, impart * cvalue);
	return temp;
}
